#pragma once

#include <memory>

namespace DB
{

class Block;

class IJoin
{
public:
    virtual ~IJoin() = default;

    /// Add block of data from right hand of JOIN.
    /// @returns false, if some limit was exceeded and you should not insert more data.
    virtual bool addJoinedBlock(const Block & block) = 0;

    /// Join the block with data from left hand of JOIN to the right hand data (that was previously built by calls to addJoinedBlock).
    /// Could be called from different threads in parallel.
    virtual void joinBlock(Block & block) = 0;

    virtual bool hasTotals() const { return false; }
    virtual void setTotals(const Block & block) = 0;
    virtual void joinTotals(Block & block) const = 0;

    virtual size_t getTotalRowCount() const = 0;
};

using JoinPtr = std::shared_ptr<IJoin>;

}
