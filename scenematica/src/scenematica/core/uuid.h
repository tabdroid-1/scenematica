#pragma once

namespace Scenematica {

class UUID {
public:
    UUID();
    UUID(uint64_t uuid);
    UUID(const UUID& other);

    uint64_t Get() const { return m_UUID; }
    bool Valid() const { return m_UUID != 0; }

    operator uint64_t() const { return m_UUID; }

private:
    uint64_t m_UUID;
};

}

namespace std {

template <>
struct hash<Scenematica::UUID> {
    size_t operator()(const Scenematica::UUID& uuid) const
    {
        return hash<uint64_t>()(uuid.Get());
    }
};

}
