#pragma once

#include <scenematica/types.h>

namespace Scenematica {

class Element { };

class MeshElement : public Element {
private:
    std::string m_TexturePath;
    std::vector<Vector2> m_Vertices;
};

}
