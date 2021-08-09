#pragma once

#include <common.hh>
#include "Layer.hh"

#include <vector>

namespace GE
{
class GE_PUBLIC LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);
    void popLayer(Layer* layer);
    void popOverlay(Layer* overlay);

    auto begin() { return m_layers.begin(); }
    auto end() { return m_layers.end(); }

private:
    std::vector<Layer*> m_layers;
    std::vector<Layer*>::iterator m_layerInsert;
};
}