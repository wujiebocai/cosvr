set(ABSL_INTERNAL_DLL_FILES
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/algorithm/algorithm.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/algorithm/container.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/attributes.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/call_once.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/casts.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/config.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/const_init.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/dynamic_annotations.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/atomic_hook.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/cycleclock.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/cycleclock.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/cycleclock_config.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/direct_mmap.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/dynamic_annotations.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/endian.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/errno_saver.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/fast_type_id.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/hide_ptr.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/identity.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/invoke.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/inline_variable.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/low_level_alloc.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/low_level_alloc.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/low_level_scheduling.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/nullability_impl.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/per_thread_tls.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/prefetch.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/prefetch.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/pretty_function.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/raw_logging.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/raw_logging.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/scheduling_mode.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/scoped_set_env.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/scoped_set_env.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/strerror.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/strerror.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/spinlock.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/spinlock.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/spinlock_wait.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/spinlock_wait.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/sysinfo.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/sysinfo.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/thread_annotations.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/thread_identity.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/thread_identity.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/throw_delegate.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/throw_delegate.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/tsan_mutex_interface.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/unaligned_access.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/unscaledcycleclock.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/unscaledcycleclock.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/internal/unscaledcycleclock_config.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/log_severity.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/log_severity.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/macros.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/nullability.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/optimization.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/options.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/policy_checks.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/port.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/base/thread_annotations.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/cleanup/cleanup.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/cleanup/internal/cleanup.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/btree_map.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/btree_set.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/fixed_array.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/flat_hash_map.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/flat_hash_set.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/inlined_vector.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/btree.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/btree_container.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/common.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/common_policy_traits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/compressed_tuple.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/container_memory.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/counting_allocator.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hash_function_defaults.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hash_policy_traits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hashtable_debug.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hashtable_debug_hooks.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hashtablez_sampler.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hashtablez_sampler.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/hashtablez_sampler_force_weak_definition.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/inlined_vector.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/layout.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/node_slot_policy.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/raw_hash_map.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/raw_hash_set.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/raw_hash_set.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/internal/tracked.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/node_hash_map.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/container/node_hash_set.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/crc32c.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/crc32c.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/cpu_detect.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/cpu_detect.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc32c.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc32c_inline.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc32_x86_arm_combined_simd.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_cord_state.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_cord_state.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_internal.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_x86_arm_combined.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_memcpy_fallback.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_memcpy.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_memcpy_x86_64.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_non_temporal_memcpy.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/crc_x86_arm_combined.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/non_temporal_arm_intrinsics.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/crc/internal/non_temporal_memcpy.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/failure_signal_handler.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/failure_signal_handler.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/leak_check.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/stacktrace.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/stacktrace.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/symbolize.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/symbolize.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/address_is_readable.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/address_is_readable.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/demangle.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/demangle.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/elf_mem_image.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/elf_mem_image.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/examine_stack.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/examine_stack.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/stack_consumption.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/stack_consumption.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/stacktrace_config.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/symbolize.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/vdso_support.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/internal/vdso_support.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/functional/any_invocable.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/functional/internal/front_binder.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/functional/bind_front.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/functional/function_ref.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/functional/internal/any_invocable.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/functional/internal/function_ref.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/hash.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/city.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/city.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/hash.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/hash.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/spy_hash_state.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/low_level_hash.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/hash/internal/low_level_hash.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/absl_check.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/absl_log.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/check.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/die_if_null.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/die_if_null.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/globals.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/globals.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/append_truncated.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/check_impl.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/check_op.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/check_op.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/conditions.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/conditions.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/config.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/globals.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/globals.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_format.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_format.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_impl.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_message.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_message.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_sink_set.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/log_sink_set.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/nullguard.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/nullguard.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/nullstream.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/proto.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/proto.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/strip.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/structured.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/internal/voidify.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/initialize.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/initialize.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log_entry.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log_entry.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log_sink.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log_sink.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log_sink_registry.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/log_streamer.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/log/structured.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/memory/memory.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/meta/type_traits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/numeric/bits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/numeric/int128.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/numeric/int128.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/numeric/internal/bits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/numeric/internal/representation.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/profiling/internal/exponential_biased.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/profiling/internal/exponential_biased.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/profiling/internal/periodic_sampler.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/profiling/internal/periodic_sampler.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/profiling/internal/sample_recorder.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/bernoulli_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/beta_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/bit_gen_ref.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/discrete_distribution.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/discrete_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/distributions.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/exponential_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/gaussian_distribution.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/gaussian_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/distribution_caller.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/fastmath.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/fast_uniform_bits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/generate_real.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/iostream_state_saver.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/nonsecure_base.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/pcg_engine.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/platform.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/pool_urbg.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/pool_urbg.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_detect.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_detect.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_engine.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_hwaes.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_hwaes.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_round_keys.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_slow.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_slow.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/randen_traits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/salted_seed_seq.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/seed_material.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/seed_material.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/sequence_urbg.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/traits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/uniform_helper.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/internal/wide_multiply.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/log_uniform_int_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/poisson_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/random.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/seed_gen_exception.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/seed_gen_exception.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/seed_sequences.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/seed_sequences.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/uniform_int_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/uniform_real_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/random/zipf_distribution.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/internal/status_internal.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/internal/statusor_internal.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/status.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/status.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/statusor.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/statusor.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/status_payload_printer.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/status/status_payload_printer.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/ascii.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/ascii.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/charconv.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/charconv.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/cord.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/cord.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/cord_analysis.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/cord_analysis.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/cord_buffer.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/cord_buffer.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/escaping.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/escaping.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/charconv_bigint.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/charconv_bigint.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/charconv_parse.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/charconv_parse.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_data_edge.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_internal.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_internal.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_btree.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_btree.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_btree_navigator.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_btree_navigator.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_btree_reader.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_btree_reader.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_crc.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_crc.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_consume.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_consume.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_flat.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_ring.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_ring.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cord_rep_ring_reader.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_functions.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_functions.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_handle.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_handle.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_info.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_info.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_sample_token.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_sample_token.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_statistics.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_update_scope.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/cordz_update_tracker.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/damerau_levenshtein_distance.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/damerau_levenshtein_distance.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/stl_type_traits.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/string_constant.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/stringify_sink.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/stringify_sink.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/has_absl_stringify.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/match.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/match.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/numbers.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/numbers.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_format.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_cat.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_cat.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_join.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_replace.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_replace.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_split.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/str_split.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/string_view.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/string_view.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/strip.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/substitute.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/substitute.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/char_map.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/escaping.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/escaping.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/memutil.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/memutil.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/ostringstream.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/ostringstream.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/pow10_helper.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/pow10_helper.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/resize_uninitialized.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/arg.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/arg.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/bind.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/bind.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/checker.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/constexpr_parser.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/extension.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/extension.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/float_conversion.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/float_conversion.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/output.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/output.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/parser.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_format/parser.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_join_internal.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/str_split_internal.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/utf8.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/strings/internal/utf8.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/barrier.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/barrier.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/blocking_counter.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/blocking_counter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/mutex.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/mutex.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/notification.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/notification.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/create_thread_identity.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/create_thread_identity.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/futex.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/futex_waiter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/futex_waiter.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/graphcycles.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/graphcycles.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/kernel_timeout.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/kernel_timeout.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/per_thread_sem.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/per_thread_sem.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/pthread_waiter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/pthread_waiter.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/sem_waiter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/sem_waiter.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/stdcpp_waiter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/stdcpp_waiter.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/thread_pool.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/waiter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/waiter_base.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/waiter_base.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/win32_waiter.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/synchronization/internal/win32_waiter.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/civil_time.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/civil_time.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/clock.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/clock.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/duration.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/format.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/time.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/time.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/include/cctz/civil_time.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/include/cctz/civil_time_detail.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/include/cctz/time_zone.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/include/cctz/zone_info_source.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/civil_time_detail.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_fixed.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_fixed.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_format.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_if.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_if.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_impl.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_impl.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_info.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_info.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_libc.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_libc.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_lookup.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_posix.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_posix.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/tzfile.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/time/internal/cctz/src/zone_info_source.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/any.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/bad_any_cast.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/bad_any_cast.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/bad_optional_access.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/bad_optional_access.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/bad_variant_access.cc
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/bad_variant_access.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/compare.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/conformance_aliases.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/conformance_archetype.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/conformance_profile.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/parentheses.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/transform_args.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/variant.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/optional.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/optional.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/span.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/internal/span.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/types/variant.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/utility/internal/if_constexpr.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/utility/utility.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp/absl/debugging/leak_check.cc
)

add_library(ABSL_LIB OBJECT ${ABSL_INTERNAL_DLL_FILES})