/*
 * Copyright (c) 2023 bocai
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#include "asio/experimental/awaitable_operators.hpp"
#include "base/queue.hpp"

using namespace asio::experimental::awaitable_operators;

namespace bnet::base {
    template<class ... Args>
	class transfer {};

	template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_tcp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public buffer_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, std::size_t max_buffer_size)
			: buffer_queue(io)
            , derive_(static_cast<DriverType&>(*this))
			, buffer_(max_buffer_size) {}

		~transfer() = default;

        template<class DataType>
        inline void send(DataType&& data) {
            this->enqueue(std::forward<DataType>(data));
		}

        template<class DataType>
        asio::awaitable<size_t> co_send(DataType&& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
				//if (data.size() <= 0)
                //    asio::detail::throw_error(asio::error::invalid_argument);

                auto [ec, nsent] = co_await asio::async_write(this->derive_.socket(),
                    asio::buffer(std::move(data)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return nsent;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                [[maybe_unused]] auto ret = co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }

    protected:
        inline void transfer_start() {
            buffer_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
			asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() { buffer_queue::uninit(); }

        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue(*this);
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

        asio::awaitable<void> recv_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    //auto [ec, nrecv] = co_await this->derive_.stream().async_read_some(this->buffer_);
                    auto [ec, nrecv] = co_await asio::async_read(this->derive_.socket(), this->buffer_, asio::transfer_at_least(1), asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    if (nrecv <= 0) continue;

                    this->handle_recv(ec, std::string_view(reinterpret_cast<
							std::string_view::const_pointer>(this->buffer_.data().data()), nrecv));

                    this->buffer_.consume(nrecv);
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

        inline void handle_recv(error_code ec, const std::string_view& s) {
            std::ignore = ec;
			this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), std::move(s));
		}

    protected:
		DriverType& derive_;

		asio::streambuf buffer_;
    };

    template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_udp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public buffer_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, [[maybe_unused]] std::size_t max_buffer_size)
			: buffer_queue(io)
            , derive_(static_cast<DriverType&>(*this))
			, buffer_() {}

		~transfer() = default;

        template<class DataType>
        inline void send(DataType&& data) {
			this->enqueue(std::forward<DataType>(data));
		}

        template<class DataType>
        asio::awaitable<size_t> co_send(DataType&& data) requires is_cli_c<SvrOrCli> {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
				//if (buffer.size() <= 0)
                //    asio::detail::throw_error(asio::error::invalid_argument);

                auto [ec, nsent] = co_await this->derive_.socket().async_send(asio::buffer(std::move(data)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return nsent;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }

        template<class DataType>
        asio::awaitable<size_t> co_send(DataType&& data) requires is_svr_c<SvrOrCli> {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
				//if (buffer.size() <= 0)
                //    asio::detail::throw_error(asio::error::invalid_argument);

                auto [ec, nsent] = co_await this->derive_.socket().async_send_to(asio::buffer(std::move(data)), 
                                        this->remote_endpoint_, asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return nsent;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }

        template<class DataType>
        asio::awaitable<size_t> co_send(std::string_view host, std::string_view port, DataType&& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
				//if (buffer.size() <= 0)
                //    asio::detail::throw_error(asio::error::invalid_argument);

                asio::ip::udp::resolver resolver(this->cio_.context());
                auto [ec, endpoints] = co_await resolver.async_resolve(host, port, asio::as_tuple(asio::use_awaitable));
			    if (ec) {
                    asio::detail::throw_error(ec);
                }

                for (auto& iter = endpoints.begin(); iter != endpoints.end(); ++iter) {
                    auto [ec, nsent] = co_await this->derive_.socket().async_send_to(asio::buffer(std::move(data)), 
                                        iter->endpoint(), asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    co_return nsent;
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }

        inline auto& remote_endpoint() { return remote_endpoint_; }
        inline void remote_endpoint(const asio::ip::udp::endpoint& endpoint) { this->remote_endpoint_ = std::move(endpoint); }
        inline auto& buffer() { return buffer_; }

        inline error_code handle_recv(error_code ec, const std::string_view& s) {
            //std::ignore = ec;
			this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), std::move(s));
            return ec;
		}
    protected:
        inline void transfer_start() {
            buffer_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
			asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() { buffer_queue::uninit(); }

        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue(*this);
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }
        
		inline asio::awaitable<void> recv_t() requires is_cli_c<SvrOrCli> {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    //this->buffer_.wr_reserve(init_buffer_size_);
                    //this->buffer_.reset();
                    auto [ec, nrecv] = co_await this->derive_.socket().async_receive(asio::mutable_buffer(this->buffer_.wr_buf(), this->buffer_.wr_size()), 
                                            asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    if (nrecv <= 0) continue;

                    //this->buffer_.wr_flip(nrecv);

					this->handle_recv(ec, std::string_view(reinterpret_cast<
						std::string_view::const_pointer>(this->buffer_.rd_buf()), nrecv));
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
		}

        inline asio::awaitable<void> recv_t() requires is_svr_c<SvrOrCli> {
            auto blen = this->buffer_.rd_size();
            if (blen > 0) {
                this->handle_recv(ec_ignore, std::string_view(reinterpret_cast<
					std::string_view::const_pointer>(this->buffer_.rd_buf()), blen));

                this->buffer_.reset();
            }
            co_return;
        }

    protected:
        DriverType& derive_;

        asio::ip::udp::endpoint remote_endpoint_;
        
        dynamic_buffer<> buffer_;
		const std::size_t init_buffer_size_ = 1024;
    };

#if defined(BNET_ENABLE_HTTP)
    template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_http_proto<ProtoType> && is_tcp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public normal_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, [[maybe_unused]] std::size_t max_buffer_size)
			: normal_queue(io)
            , derive_(static_cast<DriverType&>(*this))
            , rbuff_(max_buffer_size)
            , timer_(io.context()) { }

		~transfer() = default;

        template<class DataType>
        inline void send(DataType&& data) {
            if constexpr (is_c_str_c<DataType>) {
                this->enqueue([this, data = asio::buffer(std::move(data))]() -> asio::awaitable<error_code> {
                    return co_send(std::move(data));
                });
            }
            else {
                this->enqueue([this, data = std::move(data)]() -> asio::awaitable<error_code> {
                    return co_send(std::move(data));
                });
            }
		}

#if defined(BNET_HTTP_NOPIPELINE)
        template<class DataType, class HandleFunc>
        inline void send(DataType&& data, HandleFunc&& f) requires is_cli_c<SvrOrCli> {
            this->enqueue([this, data = std::move(data), f = std::move(f)]() -> asio::awaitable<error_code> {
                auto req_timout = (derive_.globalctx().cli_cfg_.request_timout > 0 ? derive_.globalctx().cli_cfg_.request_timout : 5);
                timer_.expires_after(std::chrono::seconds(req_timout));
                std::variant<error_code, std::monostate> rets = co_await (this->co_send_recv(std::move(data)) || timer_.async_wait(asio::use_awaitable));
                timer_.cancel();

                error_code ec;
                switch (rets.index()) {
                case 0: ec = std::get<0>(rets); break;
                case 1: ec = asio::error::timed_out; break;
                //case std::variant_npos: ec = asio::error::operation_aborted; break;
                default: ec = asio::error::operation_aborted; break;
                }

                if (ec) {
                    co_await this->derive_.co_stop(ec);
                    co_return ec;
                }

                f(ec, rep_);

                co_return ec;
            });
		}
#else
        template<class DataType, class HandleFunc>
        inline void send(DataType&& data, HandleFunc&& f) {
            if constexpr (is_c_str_c<DataType>) {
                this->enqueue([this, data = asio::buffer(std::move(data)), f = std::move(f)]() -> asio::awaitable<error_code> {
                    auto ec = co_await co_send(std::move(data));
                    if (!ec) {
                        this->derive_.cli_router().handle_func(std::move(f));
                    }
                    else {
                        f(ec, rep_);
                    }
                    co_return ec;
                });
            }
            else {
                this->enqueue([this, data = std::move(data), f = std::move(f)]() -> asio::awaitable<error_code> {
                    auto ec = co_await co_send(std::move(data));
                    if (!ec) {
                        this->derive_.cli_router().handle_func(std::move(f));
                    }
                    else {
                        f(ec, rep_);
                    }
                    co_return ec;
                });
            }
            
            auto req_timout = (derive_.globalctx().cli_cfg_.request_timout > 0 ? derive_.globalctx().cli_cfg_.request_timout : 5);
            reset_timer(timer_, std::chrono::seconds(req_timout), [this, self = this->derive_.self_shared_ptr()](const error_code& ec) {
                if (ec || this->derive_.cli_router().size() <= 0) {
                    return;
                }

                this->derive_.cli_router().handle_all(asio::error::timed_out, rep_);
                this->derive_.stop(asio::error::timed_out);
            });
		}
#endif

        template<is_string_like_or_constructible_c Data>
        asio::awaitable<error_code> co_send(Data&& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
                //if (data.size() <= 0)
                //    asio::detail::throw_error(asio::error::invalid_argument);

                auto [ec, nsent] = co_await asio::async_write(this->derive_.socket(),
                    asio::buffer(std::move(data)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return rec;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return rec;
        }

        template<bool IsRequest, class Body, class Fields>
		inline asio::awaitable<error_code> co_send(const http::message<IsRequest, Body, Fields>& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                check_http_message_t(data);

                auto [ec, nsent] = co_await http::async_write(this->derive_.socket(), data, asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return rec;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return rec;
		}

		//template<class Body, class Fields>
		//inline asio::awaitable<error_code> co_send(const http::http_request_impl_t<Body, Fields>& data) {
        //    return co_send(data.base());
		//}

		//template<class Body, class Fields>
		//inline asio::awaitable<error_code> co_send(const http::http_response_impl_t<Body, Fields>& data) {
        //    return co_send(data.base());
		//}

#if defined(BNET_HTTP_NOPIPELINE)
        template<bool IsRequest, class Body, class Fields>
        inline asio::awaitable<error_code> co_send_recv(const http::message<IsRequest, Body, Fields>& data) requires is_cli_c<SvrOrCli> {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                check_http_message_t(data);
                auto [ec, nsent] = co_await http::async_write(this->derive_.socket(), data, asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                this->rep_.reset();
                auto [rec, nrecv] = co_await http::async_read(this->derive_.socket(), rbuff_, rep_,
                                        asio::as_tuple(asio::use_awaitable));
                if (rec) {
                    asio::detail::throw_error(ec);
                }

                co_return rec;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return rec;
        }
#endif
    protected:
        inline void transfer_start() {
            normal_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
#if defined(BNET_HTTP_NOPIPELINE)
            if constexpr (is_svr_c<SvrOrCli>) 
#endif
            asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() {
            normal_queue::uninit();
            timer_.cancel();
        }

        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue();
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

        template<bool IsRequest, class Body, class Fields>
		inline void check_http_message_t(const http::message<IsRequest, Body, Fields>& msg) {
			// https://datatracker.ietf.org/doc/html/rfc2616#section-14.13
			// If an http message header don't has neither "Content-Length" nor "Transfer-Encoding"(chunk)
			// Then the receiver may not be able to parse the http message normally.
			if (!msg.chunked()) {
				if (msg.find(http::field::content_length) == msg.end()) {
					http::try_prepare_payload(const_cast<http::message<IsRequest, Body, Fields>&>(msg));
				}
			}
		}

        inline asio::awaitable<void> recv_t() requires is_svr_c<SvrOrCli> {
            error_code rec;
            try {
                set_rsp_refresh();
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    // Make the request empty before reading,
				    // otherwise the operation behavior is undefined.
				    this->req_.reset();
                    auto [ec, nrecv] = co_await http::async_read(this->derive_.socket(), rbuff_, req_,
                                            asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    std::string_view target = this->req_.target();
				    http::http_parser_parse_url(
					    target.data(), target.size(), 0, std::addressof(req_.get_url().parser()));
                        
                    rep_.result(http::status::unknown);
				    rep_.keep_alive(req_.keep_alive());
                    
                    co_await this->handle_recv_s();
                    //auto ret = co_await this->handle_recv_s();
                    //if (ret == 0) {
                    //    std::cout << "http handle request fail:" << req_.target() << std::endl;
                    //}
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
		}

        inline asio::awaitable<void> recv_t() requires is_cli_c<SvrOrCli> {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    // Make the request empty before reading,
				    // otherwise the operation behavior is undefined.
				    this->rep_.reset();

                    auto [ec, nrecv] = co_await http::async_read(this->derive_.socket(), rbuff_, rep_,
                                            asio::as_tuple(asio::use_awaitable));
                    
                    this->handle_recv_c(ec);

                    if (ec) {
                        asio::detail::throw_error(ec);
                    }
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
		}

        inline asio::awaitable<void> handle_recv_s() {
            std::string path(this->req_.path());
            auto method = this->req_.method();
            auto ret = this->derive_.globalctx().handle(method, path);

            if (ret && (*ret).handlers_) {
                (*ret).handlers_(req_, rep_);
            }
            else {
                this->derive_.fill_route_fail(req_, rep_);
                co_await this->co_send(rep_);
            }
            co_return;
		}

        inline void handle_recv_c(const error_code& ec) {
            //this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), req_, rep_);
            //auto func = this->derive_.cli_router().handle();
            //if (func) {
            //    func(req_, rep_);
            //}
            this->derive_.cli_router().handle(ec, rep_);
        }

        inline void set_rsp_refresh() {
            std::weak_ptr<DriverType> wptr = this->derive_.self_shared_ptr();
            rep_.refresh([wptr] (const http::web_response& rep) mutable {
                auto sptr = wptr.lock();
                if (sptr) {
                    sptr->send(rep);
                }
            });
        }

    protected:
        DriverType& derive_;
        beast::flat_buffer rbuff_;
        http::web_request req_;
		http::web_response rep_;
        asio::steady_timer timer_;
    };
#endif

#if defined(BNET_ENABLE_HTTP)
    template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_ws_proto<ProtoType> && is_tcp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public buffer_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, [[maybe_unused]] std::size_t max_buffer_size)
			: buffer_queue(io)
            , derive_(static_cast<DriverType&>(*this)) {}

		~transfer() = default;

        template<class DataType>
        inline void send(DataType&& data) {
            this->enqueue(std::forward<DataType>(data));
		}

        //template<is_string_like_or_constructible_c DataType>
        template<class DataType>
        asio::awaitable<size_t> co_send(DataType&& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                auto [ec, nsent] = co_await this->derive_.stream().async_write(asio::buffer(std::move(data)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return nsent;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }
/*
        template<bool IsRequest, class Body, class Fields>
        asio::awaitable<size_t> co_send(http::message<IsRequest, Body, Fields>& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
				
                std::ostringstream oss;
			    oss << data;

                auto [ec, nsent] = co_await this->derive_.stream().async_write(asio::buffer(oss.str()), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return nsent;
            }
            catch (system_error& e) {
                rec = e.code(); 
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }

		template<class Body, class Fields>
		inline asio::awaitable<size_t> co_send(http::http_request_impl_t<Body, Fields>& data) {
			return this->co_send(data.base());
		}

		template<class Body, class Fields>
		inline asio::awaitable<size_t> co_send(http::http_response_impl_t<Body, Fields>& data) {
			return this->co_send(data.base());
		}
*/
    protected:
        inline void transfer_start() {
            buffer_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
			asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() { buffer_queue::uninit(); }

        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue(*this);
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

        inline asio::awaitable<error_code> recv_t() {
            error_code rec;
            try {
                auto& buffer = this->derive_.ws_buffer();
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    auto [ec, nrecv] = co_await this->derive_.stream().async_read(buffer, asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    // bytes_recvd : The number of bytes in the streambuf's get area up to and including the delimiter.
                    if (nrecv <= 0) continue;

                    this->handle_recv(ec, std::string_view(reinterpret_cast<
							std::string_view::const_pointer>(buffer.data().data()), nrecv));

                    buffer.consume(nrecv);
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
		}

        inline void handle_recv(error_code ec, const std::string_view& s) {
            std::ignore = ec;
			this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), std::move(s));
		}

        //inline websocket::request_type& upgrade_req() { return upgrade_req_; }
    protected:
        DriverType& derive_;
    };
#endif

    template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_kcp_stream<StreamType> && is_udp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public buffer_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, [[maybe_unused]] std::size_t max_buffer_size)
			: buffer_queue(io)
            , derive_(static_cast<DriverType&>(*this))
			, buffer_() {}

		~transfer() = default;

        template<class DataType>
        inline void send(DataType&& data) {
            this->enqueue(std::forward<DataType>(data));
		}

        template<class DataType>
        asio::awaitable<size_t> co_send(DataType&& data) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
                auto buffer = asio::buffer(std::move(data));
				if (buffer.size() <= 0)
                    asio::detail::throw_error(asio::error::invalid_argument);

                int ret = kcp::ikcp_send(this->derive_.kcp(), (const char *)buffer.data(), (int)buffer.size());

			    switch (ret) {
			    case  0: break;
			    case -1: asio::detail::throw_error(asio::error::invalid_argument       ); break;
			    case -2: asio::detail::throw_error(asio::error::no_memory              ); break;
			    default: asio::detail::throw_error(asio::error::operation_not_supported); break;
			    }

			    if (ret == 0) {
			    	kcp::ikcp_flush(this->derive_.kcp());
			    }

                co_return buffer.size();
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return 0;
        }

        inline auto& buffer() { return buffer_; }

        inline error_code handle_recv(error_code ec, std::string_view s) {
            if (ec) {
                return ec;
            }
			//this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), std::move(s));
            auto ptr = this->derive_.self_shared_ptr();
            auto kec = this->derive_.kcp_handle_recv_t(ptr, s);
            if (kec) {
                return kec;
            }

            return ec_ignore;
		}
    protected:
        inline void transfer_start() {
            buffer_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
			asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() { buffer_queue::uninit(); }
/*
        template<class Buffer>
		inline asio::awaitable<std::size_t> send_t(Buffer&& buffer) requires is_cli_c<SvrOrCli> {
			auto buffer = asio::buffer(std::move(data));

			int ret = kcp::ikcp_send(this->derive_.kcp(), (const char *)buffer.data(), (int)buffer.size());

			switch (ret) {
			case  0: set_last_error(error_code{}                        ); break;
			case -1: set_last_error(asio::error::invalid_argument       ); break;
			case -2: set_last_error(asio::error::no_memory              ); break;
			default: set_last_error(asio::error::operation_not_supported); break;
			}

			if (ret == 0) {
				kcp::ikcp_flush(this->derive_.kcp());
			}

			return std::size_t(ret);
		}
*/      
        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue(*this);
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

		inline asio::awaitable<void> recv_t() requires is_cli_c<SvrOrCli> {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    //this->buffer_.wr_reserve(init_buffer_size_);
                    //this->buffer_.reset();
                    auto [ec, nrecv] = co_await this->derive_.socket().async_receive(asio::mutable_buffer(this->buffer_.wr_buf(), this->buffer_.wr_size()), 
                                            asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    if (nrecv <= 0) continue;

                    //this->buffer_.wr_flip(nrecv);

					//this->handle_recv(ec, std::string_view(reinterpret_cast<
					//	std::string_view::const_pointer>(this->buffer_.rd_buf()), nrecv));
                    ec = this->handle_recv(ec, std::string_view(reinterpret_cast<
						std::string_view::const_pointer>(this->buffer_.rd_buf()), nrecv));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
		}

        inline asio::awaitable<void> recv_t() requires is_svr_c<SvrOrCli> {
            //auto ptr = this->derive_.self_shared_ptr();
            //auto ec = this->derive_.kcp_handle_recv_t(ptr, ec);
            //if (ec) {
            //    co_return ec;
            //}
            auto ec = this->handle_recv(ec_ignore, std::string_view(reinterpret_cast<
				std::string_view::const_pointer>(this->buffer_.rd_buf()), this->buffer_.rd_size()));
            if (ec) {
                co_await this->derive_.co_stop(ec);
            }

            this->buffer_.reset();
        }

    protected:
        DriverType& derive_;
        
        dynamic_buffer<> buffer_;
		const std::size_t init_buffer_size_ = 1024;
    };

    template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_rpc_proto<ProtoType> && is_tcp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public normal_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, [[maybe_unused]] std::size_t max_buffer_size)
			: normal_queue(io)
            , derive_(static_cast<DriverType&>(*this))
            , timer_(io.context()) { }

		~transfer() = default;

        template<class CbFunc, class... Args>
        inline void request(CbFunc&& f, Args&&... args) requires is_cli_c<SvrOrCli> {
            this->enqueue([this, f = std::move(f), ... args = std::move(args)]() -> asio::awaitable<error_code> {
                auto req_timout = (derive_.globalctx().cli_cfg_.request_timout > 0 ? derive_.globalctx().cli_cfg_.request_timout : 5);
                timer_.expires_after(std::chrono::seconds(req_timout));
                std::variant<error_code, std::monostate> rets = co_await (this->co_request(std::move(args)...) || timer_.async_wait(asio::use_awaitable));
                timer_.cancel();

                error_code ec;
                switch (rets.index()) {
                case 0: ec = std::get<0>(rets); break;
                case 1: ec = asio::error::timed_out; break;
                //case std::variant_npos: ec = asio::error::operation_aborted; break;
                default: ec = asio::error::operation_aborted; break;
                }

                if (ec) {
                    co_await this->derive_.co_stop(ec);
                    co_return ec;
                }

                f(this->derive_.self_shared_ptr(), ec, rsp_header_,std::string_view(reinterpret_cast<
						    std::string_view::const_pointer>(this->buffer_.rd_buf()), this->buffer_.rd_size()));

                co_return ec; 
            });
		}

        template<class... Args>
        inline void response(Args&&... args) requires is_svr_c<SvrOrCli> {
            this->enqueue([this, ... args = std::move(args)]() -> asio::awaitable<error_code> {
                return this->co_response(std::move(args)...);
            });
		}

    protected:
        template<class... Args>
        inline asio::awaitable<error_code> co_request(Args&&... args) requires is_cli_c<SvrOrCli> {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);
                
                using buffer_type = dynamic_buffer<>;
                constexpr bool is_pack_req = requires { ProtoType::pack_req(buffer_type{}, std::forward<Args>(args)...); };
                if constexpr (is_pack_req) 
                    asio::detail::throw_error(asio::error::no_protocol_option);
                
                this->buffer_.reset();
                ProtoType::pack_req(this->buffer_, std::forward<Args>(args)...);
                auto [ec, len] = co_await asio::async_write(this->derive_.socket(),
                        asio::buffer(this->buffer_.rd_buf(), this->buffer_.rd_size()), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                std::tie(ec, len) = co_await asio::async_read(this->derive_.socket(), asio::buffer((char *)&rsp_header_, ProtoType::RSP_HEAD_SIZE), 
                                                    asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                uint32_t body_len = rsp_header_.length;
                this->buffer_.reset();
                this->buffer_.wr_reserve(body_len);
                std::tie(ec, len) = co_await asio::async_read(this->derive_.socket(), asio::buffer(this->buffer_.wr_buf(), body_len), 
                                                    asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                this->buffer_.wr_flip(len);

                co_return rec;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            //if (rec) {
            //    co_await this->derive_.co_stop(rec);
            //}

            co_return rec;
        }

        template<class... Args>
        inline asio::awaitable<error_code> co_response(Args&&... args) requires is_svr_c<SvrOrCli> {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                using buffer_type = dynamic_buffer<>;
                constexpr bool is_pack_rsp = requires { ProtoType::pack_rsp(buffer_type{}, std::forward<Args>(args)...); };
                if constexpr (is_pack_rsp) 
                    asio::detail::throw_error(asio::error::no_protocol_option);

                buffer_type buffer;
                ProtoType::pack_rsp(buffer, std::forward<Args>(args)...);
                auto [ec, nsent] = co_await asio::async_write(this->derive_.socket(),
                        asio::buffer(buffer.rd_buf(), buffer.rd_size()), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return rec;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return rec;
        }

        inline asio::awaitable<void> recv_t() requires is_svr_c<SvrOrCli> {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    reset_timer();
                    auto [ec, nrecv] = co_await asio::async_read(this->derive_.socket(), asio::buffer((char *)&req_header_, ProtoType::REQ_HEAD_SIZE), 
                                                    asio::as_tuple(asio::use_awaitable));
                    cancel_timer();
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    uint32_t body_len = req_header_.length;
                    //this->buffer_.reset();
                    this->buffer_.wr_reserve(body_len);
                    std::tie(ec, nrecv) = co_await asio::async_read(this->derive_.socket(), asio::buffer(this->buffer_.wr_buf(), body_len), 
                                                    asio::as_tuple(asio::use_awaitable));
                    if (ec) {
                        asio::detail::throw_error(ec);
                    }

                    this->handle_recv(ec, req_header_, std::string_view(reinterpret_cast<
						    std::string_view::const_pointer>(this->buffer_.rd_buf()), nrecv));
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
		}

        void reset_timer() {
            if (!enable_check_timeout_) {
                return;
            }

            timer_.expires_after(std::chrono::seconds(5));
            timer_.async_wait(
                [this, self = this->derive_.shared_from_this()](asio::error_code const &ec) {
                if (!ec) {
                    std::cout << "close session timeout" << std::endl;
                    self->stop(asio::error::timed_out);
                }
            });
        }

        void cancel_timer() {
            if (!enable_check_timeout_) {
                return;
            }

            timer_.cancel();
        }

        inline void handle_recv(error_code ec, typename ProtoType::req_header& header, const std::string_view& s) {
            //std::ignore = ec;
			this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), ec, header, std::move(s));
		}

        inline void transfer_start() {
            normal_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
            if constexpr (is_svr_c<SvrOrCli>) 
                asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() {
            normal_queue::uninit();
            timer_.cancel();
        }

        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue();
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

    protected:
        DriverType& derive_;
        typename ProtoType::req_header req_header_;
        typename ProtoType::rsp_header rsp_header_;
        dynamic_buffer<> buffer_;
        asio::steady_timer timer_;
        bool enable_check_timeout_ = false;
    };

    template<class DriverType, class StreamType, class ProtoType, class SvrOrCli> 
    requires is_txt_proto<ProtoType> && is_tcp_by_stream<StreamType>
	class transfer<DriverType, StreamType, ProtoType, SvrOrCli> : public normal_queue {
    public:
        using transfer_type = transfer<DriverType, StreamType, ProtoType, SvrOrCli>;
	public:
		transfer([[maybe_unused]]nio & io, [[maybe_unused]] std::size_t max_buffer_size)
			: normal_queue(io)
            , derive_(static_cast<DriverType&>(*this))
            , timer_(io.context()) { }

		~transfer() = default;

        template<class CbFunc, class Buffer>
        inline void request(CbFunc&& f, Buffer&& buffer) requires is_cli_c<SvrOrCli> {
            this->enqueue([this, f = std::move(f), buffer = data_conv(std::move(buffer))]() -> asio::awaitable<error_code> {
                using result_type = last_parameters_type_t<CbFunc>;
                result_type ret;

                if (is_loop_recv) {
                    f(this->derive_.self_shared_ptr(), asio::error::operation_aborted, ret);
                    co_return asio::error::operation_aborted; 
                }

                auto req_timout = (derive_.globalctx().cli_cfg_.request_timout > 0 ? derive_.globalctx().cli_cfg_.request_timout : 5);
                timer_.expires_after(std::chrono::seconds(req_timout));
                std::variant<error_code, std::monostate> rets = co_await (this->co_request(ret, std::move(buffer)) || timer_.async_wait(asio::use_awaitable));
                timer_.cancel();

                error_code ec;
                switch (rets.index()) {
                case 0: ec = std::get<0>(rets); break;
                case 1: ec = asio::error::timed_out; break;
                //case std::variant_npos: ec = asio::error::operation_aborted; break;
                default: ec = asio::error::operation_aborted; break;
                }

                if (ec) {
                    co_await this->derive_.co_stop(ec);
                    co_return ec;
                }

                f(this->derive_.self_shared_ptr(), ec, ret);

                co_return ec; 
            });
		}

        template<class CbFunc, class Buffer>
        inline void send(CbFunc&& f, Buffer&& buffer) requires is_cli_c<SvrOrCli> {
            this->enqueue([this, buffer = data_conv(std::move(buffer)), f = std::move(f)]() -> asio::awaitable<error_code> {
                auto ret = co_await this->co_send(std::move(buffer));
                f(ret);
                co_return ret;
            });
        }

        inline void monitor() requires is_cli_c<SvrOrCli> {
            if (is_loop_recv) return;
            asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
        }

        inline void close_monitor() requires is_cli_c<SvrOrCli> { is_loop_recv = false; }

        template<class Buffer>
        inline void response(Buffer&& buffer) requires is_svr_c<SvrOrCli> {
            this->enqueue([this, buffer = data_conv(std::move(buffer))]() -> asio::awaitable<error_code> {
                return this->co_send(std::move(buffer));
            });
		}

    protected:
        template<class Result, class Buffer>
        inline asio::awaitable<error_code> co_request(Result&& ret, Buffer&& buffer) requires is_cli_c<SvrOrCli> && is_txt_proto_match<ProtoType> {
            error_code rec;
            using iterator = asio::buffers_iterator<asio::streambuf::const_buffers_type>;
		    //using diff_type = typename iterator::difference_type;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                auto [ec, len] = co_await asio::async_write(this->derive_.socket(),
                        asio::buffer(std::move(buffer)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                std::function<std::pair<iterator, bool>(iterator begin, iterator end)> match_function = [&ret](iterator begin, iterator end) -> std::pair<iterator, bool> {
                    return ProtoType::match_func(begin, end, ret);
                };

                this->read_buf_.consume(this->read_buf_.size());
                std::tie(ec, len) = co_await asio::async_read_until(this->derive_.socket(), read_buf_, match_function,
                                                    asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                //this->read_buf_.consume(len);
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }

            co_return rec;
        }

        template<class Result, class Buffer>
        inline asio::awaitable<error_code> co_request(Result&& ret, Buffer&& buffer) requires is_cli_c<SvrOrCli> && is_txt_proto_cli_delim<ProtoType> {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                auto [ec, len] = co_await asio::async_write(this->derive_.socket(),
                        asio::buffer(std::move(buffer)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                this->read_buf_.consume(this->read_buf_.size());
                std::tie(ec, len) = co_await asio::async_read_until(this->derive_.socket(), read_buf_, ProtoType::cli_delim(),
                                                    asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                //this->read_buf_.consume(len);
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }

            co_return rec;
        }

        template<class Buffer>
        inline asio::awaitable<error_code> co_send(Buffer&& buffer) {
            error_code rec;
            try {
                if (!this->derive_.is_started())
                    asio::detail::throw_error(asio::error::not_connected);

                auto [ec, nsent] = co_await asio::async_write(this->derive_.socket(),
                        asio::buffer(std::move(buffer)), asio::as_tuple(asio::use_awaitable));
                if (ec) {
                    asio::detail::throw_error(ec);
                }

                co_return rec;
            }
            catch (system_error& e) {
                rec = e.code();
            }
            catch (std::exception&) { set_last_error(asio::error::eof); }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }

            co_return rec;
        }

        inline void transfer_start() {
            normal_queue::init();
            asio::co_spawn(this->derive_.cio().context(), send_t(), asio::detached);
            if constexpr (is_svr_c<SvrOrCli>) 
                asio::co_spawn(this->derive_.cio().context(), recv_t(), asio::detached);
		}
        inline void transfer_stop() {
            normal_queue::uninit();
            timer_.cancel();
        }

        inline asio::awaitable<void> recv_t() {
            if (is_loop_recv) co_return;
            is_loop_recv = true;
            
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                if constexpr (is_txt_proto_match<ProtoType>) {
                    using iterator = asio::buffers_iterator<asio::streambuf::const_buffers_type>;
                    typename ProtoType::result_type ret;
                    std::function<std::pair<iterator, bool>(iterator begin, iterator end)> match_function = [&ret](iterator begin, iterator end) -> std::pair<iterator, bool> {
                        return ProtoType::match_func(begin, end, ret);
                    };

                    while (dself->is_started()) {
                        //this->read_buf_.consume(this->read_buf_.size());
                        auto [ec, len] = co_await asio::async_read_until(this->derive_.socket(), read_buf_, match_function,
                                                    asio::as_tuple(asio::use_awaitable));
                        if (ec) {
                            asio::detail::throw_error(ec);
                        }

                        this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), ret);
                        this->read_buf_.consume(len);
                        ret.reset();

                        if (!is_loop_recv) break;
                    }
                }
                else if constexpr (is_txt_proto_cli_delim<ProtoType>) {
                    std::string delim("\r\n");
                    if constexpr (is_txt_proto_svr_delim<ProtoType>) {
                        delim = ProtoType::svr_delim();
                    }
                    else if constexpr (is_txt_proto_cli_delim<ProtoType>) {
                        delim = ProtoType::cli_delim();
                    }
                    while (dself->is_started()) {
                        auto [ec, len] = co_await asio::async_read_until(this->derive_.socket(), read_buf_, delim,
                                                    asio::as_tuple(asio::use_awaitable));
                        if (ec) {
                            asio::detail::throw_error(ec);
                        }
                        this->derive_.bind_func()->call(event::recv, this->derive_.self_shared_ptr(), std::string_view(reinterpret_cast<
						        std::string_view::const_pointer>(this->read_buf_.data().data()), len));
                        this->read_buf_.consume(len);

                        if (!is_loop_recv) break;
                    }
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                is_loop_recv = false;
                co_await this->derive_.co_stop(rec);
            }
		}

        void reset_timer() {
            if (!enable_check_timeout_) {
                return;
            }

            timer_.expires_after(std::chrono::seconds(5));
            timer_.async_wait(
                [this, self = this->derive_.shared_from_this()](asio::error_code const &ec) {
                if (!ec) {
                    std::cout << "close session timeout" << std::endl;
                    self->stop(asio::error::timed_out);
                }
            });
        }

        void cancel_timer() {
            if (!enable_check_timeout_) {
                return;
            }

            timer_.cancel();
        }

        inline asio::awaitable<void> send_t() {
            error_code rec;
            try {
                auto dself = this->derive_.self_shared_ptr();
                while (dself->is_started()) {
                    co_await this->dequeue();
                }
            }
            catch (system_error& e) {
                rec = e.code();
            }
            if (rec) {
                co_await this->derive_.co_stop(rec);
            }
        }

    protected:
        DriverType& derive_;
        asio::streambuf read_buf_;
        asio::steady_timer timer_;
        bool enable_check_timeout_ = false;
        std::atomic<bool> is_loop_recv = false;
    };
}