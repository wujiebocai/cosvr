#pragma once

#include "uuid/uuid.hpp"

modules::uuid_t operator"" _uuid(const char* cstr, size_t cstr_len) {
    static modules::uuid_t none;
    if (cstr_len != 36)
        //this_test.fail("malformed test input");
        return none;
    std::string str{cstr, cstr_len};
    if (str[8] != '-' || str[13] != '-' || str[18] != '-' || str[23] != '-')
        //this_test.fail("malformed test input");
        return none;
    str.erase(std::remove(str.begin(), str.end(), '-'), str.end());
    if (str.size() != 32)
        //this_test.fail("malformed test input");
        return none;
    modules::uuid_t result;
    for (size_t index = 0; index < 16; ++index) {
        auto input_index = index * 2;
        char buf[] = {str[input_index], str[input_index + 1], '\0'};
        result.bytes().at(index)
        = static_cast<std::byte>(std::stoi(buf, nullptr, 16));
    }
    return result;
}

#define WITH(uuid_str) if (auto x = uuid_str##_uuid; true)

void test_uuid() {
    std::cout << "==================== test uuid begin ===================" << std::endl;
    modules::uuid_t nil; // 00000000-0000-0000-0000-000000000000
    // A couple of UUIDs for version 1.
    modules::uuid_t v1[3] = {
      "cbba341a-6ceb-11ea-bc55-0242ac130003"_uuid,
      "cbba369a-6ceb-11ea-bc55-0242ac130003"_uuid,
      "cbba38fc-6ceb-11ea-bc55-0242ac130003"_uuid,
    };
    // A couple of UUIDs for version 4.
    modules::uuid_t v4[3] = {
      "2ee4ded7-69c0-4dd6-876d-02e446b21784"_uuid,
      "934a33b6-7f0c-4d70-9749-5ad4292358dd"_uuid,
      "bf761f7c-00f2-4161-855e-e286cfa63c11"_uuid,
    };

    if (to_string(nil) != "00000000-0000-0000-0000-000000000000") {
        std::cout << "test nil fail" << std::endl;
    }

    if (to_string(v1[0]) != "cbba341a-6ceb-11ea-bc55-0242ac130003") {
        std::cout << "test v1[0] fail" << std::endl;
    }
    if (to_string(v1[1]) != "cbba369a-6ceb-11ea-bc55-0242ac130003") {
        std::cout << "test v1[1] fail" << std::endl;
    }
    if (to_string(v1[2]) != "cbba38fc-6ceb-11ea-bc55-0242ac130003") {
        std::cout << "test v1[2] fail" << std::endl;
    }

    if (modules::make_uuid("00000000-0000-0000-0000-000000000000").value() != nil) {
        std::cout << "test make nil fail" << std::endl;
    }

    if (modules::make_uuid("cbba341a-6ceb-11ea-bc55-0242ac130003").value() != v1[0]) {
        std::cout << "test make v1[0] fail" << std::endl;
    }
    if (modules::make_uuid("cbba369a-6ceb-11ea-bc55-0242ac130003").value() != v1[1]) {
        std::cout << "test make v1[1] fail" << std::endl;
    }
    if (modules::make_uuid("cbba38fc-6ceb-11ea-bc55-0242ac130003").value() != v1[2]) {
        std::cout << "test make v1[2] fail" << std::endl;
    }

    if (v1[0].version() != modules::uuid::time_based) {
        std::cout << "test v1[0] version fail" << std::endl;
    }
    if (v1[1].version() != modules::uuid::time_based) {
        std::cout << "test v1[1] version fail" << std::endl;
    }
    if (v1[2].version() != modules::uuid::time_based) {
        std::cout << "test v1[2] version fail" << std::endl;
    }

    if (v4[0].version() != modules::uuid::randomized) {
        std::cout << "test v4[0] version fail" << std::endl;
    }
    if (v4[1].version() != modules::uuid::randomized) {
        std::cout << "test v4[1] version fail" << std::endl;
    }
    if (v4[2].version() != modules::uuid::randomized) {
        std::cout << "test v4[2] version fail" << std::endl;
    }

    WITH("00000001-0000-1000-8122-334455667788") {
        if (x.variant() != modules::uuid::rfc4122) {
            std::cout << "test variant fail" << std::endl;
        }
        if (x.version() != modules::uuid::time_based) {
            std::cout << "test version fail" << std::endl;
        }
        if (x.timestamp() != 0x0000000000000001ull) {
            std::cout << "test timestamp fail" << std::endl;
        }
        if (x.clock_sequence() != 0x0122u) {
            std::cout << "test clock_sequence fail" << std::endl;
        }
        if (x.node() != 0x334455667788ull) {
            std::cout << "test node fail" << std::endl;
        }
    }
    WITH("00000001-0001-1000-8122-334455667788") {
        if (x.variant() != modules::uuid::rfc4122) {
            std::cout << "test variant fail" << std::endl;
        }
        if (x.version() != modules::uuid::time_based) {
            std::cout << "test version fail" << std::endl;
        }
        if (x.timestamp() != 0x0000000100000001ull) {
            std::cout << "test timestamp fail" << std::endl;
        }
        if (x.clock_sequence() != 0x0122u) {
            std::cout << "test clock_sequence fail" << std::endl;
        }
        if (x.node() != 0x334455667788ull) {
            std::cout << "test node fail" << std::endl;
        }
    }
    WITH("00000001-0001-1001-8122-334455667788") {
        if (x.variant() != modules::uuid::rfc4122) {
            std::cout << "test variant fail" << std::endl;
        }
        if (x.version() != modules::uuid::time_based) {
            std::cout << "test version fail" << std::endl;
        }
        if (x.timestamp() != 0x0001000100000001ull) {
            std::cout << "test timestamp fail" << std::endl;
        }
        if (x.clock_sequence() != 0x0122u) {
            std::cout << "test clock_sequence fail" << std::endl;
        }
        if (x.node() != 0x334455667788ull) {
            std::cout << "test node fail" << std::endl;
        }
    }
    WITH("ffffffff-ffff-1fff-bfff-334455667788") {
        if (x.variant() != modules::uuid::rfc4122) {
            std::cout << "test variant fail" << std::endl;
        }
        if (x.version() != modules::uuid::time_based) {
            std::cout << "test version fail" << std::endl;
        }
        if (x.timestamp() != 0x0FFFFFFFFFFFFFFFull) {
            std::cout << "test timestamp fail" << std::endl;
        }
        if (x.clock_sequence() != 0x3FFFu) {
            std::cout << "test clock_sequence fail" << std::endl;
        }
        if (x.node() != 0x334455667788ull) {
            std::cout << "test node fail" << std::endl;
        }    
    }

    if (modules::uuid_t::can_parse("cbba341a-6ceb-81ea-bc55-0242ac130003")) {
        std::cout << "test can_parse fail" << std::endl;
    }
    if (modules::uuid_t::can_parse("cbba369a-6ceb-F1ea-bc55-0242ac130003")) {
        std::cout << "test can_parse fail" << std::endl;
    }
    if (modules::uuid_t::can_parse("cbba38fc-6ceb-01ea-bc55-0242ac130003")) {
        std::cout << "test can_parse fail" << std::endl;
    }

    if (modules::make_uuid("cbba341a-6ceb-81ea-bc55-0242ac130003").error().value() != static_cast<uint8_t>(modules::pec::invalid_argument)) {
        std::cout << "test make_uuid fail" << std::endl;
    }
    if (modules::make_uuid("cbba369a-6ceb-F1ea-bc55-0242ac130003").error().value() != static_cast<uint8_t>(modules::pec::invalid_argument)) {
        std::cout << "test make_uuid fail" << std::endl;
    }
    if (modules::make_uuid("cbba38fc-6ceb-01ea-bc55-0242ac130003").error().value() != static_cast<uint8_t>(modules::pec::invalid_argument)) {
        std::cout << "test make_uuid fail" << std::endl;
    }

    auto id1 = "2ee4ded7-69c0-4dd6-876d-02e446b21784"_uuid;
    auto id2 = "a6155548-2994-4833-b4e3-9823f5f15fe9"_uuid;
    std::hash<modules::uuid_t> f;
    if (id1.hash() != f(id1)) {
        std::cout << "test hash fail" << std::endl;
    }
    if (id2.hash() != f(id2)) {
        std::cout << "test hash fail" << std::endl;
    }
    if (f(id1) == f(id2)) {
        std::cout << "test hash fail" << std::endl;
    }

    std::cout << "==================== test uuid end ===================" << std::endl;
}