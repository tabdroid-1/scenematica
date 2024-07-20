#pragma once

#include <scenematica/types.h>
#include <scenematica/material.h>

namespace Scenematica {

enum ElementType : uint8_t {
    Brush = 0,
    Detail,
    Spawpoint,
};

// This is mesh with collision(can be trigger) which can be disabled.(Collision is done by user)
// If brush is big, editor will cut it in to multiple piceces and give AABB which can be used for culling.
// TODO: Give AABB
struct BrushProps {
    Material material;
    std::vector<Vector2> vertices;
    bool hasCollision;
    bool isTrigger;
    bool castShadow;
};

// This is for level details that will not move and will not have any function.
// Just visual. This contains string which user will read and deal them self in their
// engine of choice.
// TODO: Create global detail list for level registry instead of just string
// to eliminate typos.
// TODO: Give AABB
struct DetailProps {
    Material material;
    std::string detailName;
};

// This holds type of entity that this will spawn.(Spawning is done by user side.)
// TODO: Create global entity list for level registry instead of just string
// to eliminate typos.
struct SpawpointProps {
    std::string entityName;
};

class Element {
public:
    Element()
        : m_Name(std::to_string(m_UUID.Get()))
        , m_IsVisible(true)
        , m_ParentElement(0)
        , m_Type(ElementType::Brush)
        , m_Scale(1.0f, 1.0f, 1.0f)
    {
    }

    Element(const std::string& name)
        : m_Name(std::to_string(m_UUID.Get()))
        , m_IsVisible(true)
        , m_ParentElement(0)
        , m_Type(ElementType::Brush)
        , m_Scale(1.0f, 1.0f, 1.0f)
    {
    }

    UUID GetUUID() { return m_UUID; }

    bool IsVisible() { return m_IsVisible; }
    void SetIsVisible(bool visible) { m_IsVisible = visible; }

    void SetName(const std::string& name) { m_Name = name; }
    const std::string& GetName() { return m_Name; }

    void SetType(ElementType type) { m_Type = type; }
    ElementType GetType() { return m_Type; }

    void SetPosition(const Vector3& position) { m_Position = position; }
    void SetRotation(const Vector3& rotation) { m_Rotation = rotation; }
    void SetScale(const Vector3& scale) { m_Scale = scale; }

    const Vector3& GetPosition() { return m_Position; }
    const Vector3& GetRotation() { return m_Rotation; }
    const Vector3& GetScale() { return m_Scale; }

    UUID GetParent() { return m_ParentElement; }
    void SetParent(UUID parentID) { m_ParentElement = parentID; }
    void AddChildren(UUID childID) { m_ChildElementIDs.push_back(childID); }
    std::vector<UUID>& GetChildren() { return m_ChildElementIDs; }

    BrushProps& GetBrushProperties() { return m_BrushProperties; }
    DetailProps& GetDetialProperties() { return m_DetailProperties; }
    SpawpointProps& GetSpawnpointProperties() { return m_SpawnpointProperties; }

private:
    UUID m_UUID;
    bool m_IsVisible;
    std::string m_Name;
    ElementType m_Type;

    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;

    BrushProps m_BrushProperties;
    DetailProps m_DetailProperties;
    SpawpointProps m_SpawnpointProperties;

    UUID m_ParentElement;
    std::vector<UUID> m_ChildElementIDs;
};
}
