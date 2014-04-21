/*
 * Copyright (c) 2014, Hewlett-Packard Development Company, LP.
 * The license and distribution terms for this file are placed in LICENSE.txt.
 */
#ifndef FOEDUS_STORAGE_RECORD_HPP_
#define FOEDUS_STORAGE_RECORD_HPP_
#include <foedus/cxx11.hpp>
#include <foedus/storage/storage_id.hpp>
#include <foedus/xct/xct_id.hpp>
namespace foedus {
namespace storage {
/**
 * @brief Represents one record in our key-value store.
 * @ingroup STORAGE
 * @details
 * This layout is used in all storage types for "value" part.
 * @attention Do NOT instantiate this object or derive from this class.
 * A record is always reinterpret-ed from a data page. No meaningful RTTI nor copy/move semantics.
 */
struct Record CXX11_FINAL {
    /**
     * This indicates the transaction that most recently modified this record.
     * This is also used as lock/delete flag.
     * Thus, for atomic operations, Record object must be 8-byte aligned.
     */
    xct::XctId          owner_id_;

    /**
     * Arbitrary payload given by the user. The size is actually meaningless (8 is just to not
     * confuse compiler variable layout).
     */
    char                payload_[8];

    Record() CXX11_FUNC_DELETE;
    Record(const Record& other) CXX11_FUNC_DELETE;
    Record& operator=(const Record& other) CXX11_FUNC_DELETE;
};

/**
 * @brief bluh.
 * @ingroup ARRAY
 */
const uint16_t RECORD_OVERHEAD = sizeof(xct::XctId);

CXX11_STATIC_ASSERT(RECORD_OVERHEAD == sizeof(Record) - 8, "RECORD_OVERHEAD is incorrect");

}  // namespace storage
}  // namespace foedus
#endif  // FOEDUS_STORAGE_RECORD_HPP_