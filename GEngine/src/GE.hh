#pragma once

// Entry Point
// #include "geMain.hh"

#include "App.hh"
#include "utils/Logger.hh"
#include "utils/Instrumentor.hh"

#include "Time.hh"

#include "layers/Layer.hh"
#include "layers/ImGui/ImGuiLayer.hh"

#include "window/Input.hh"
#include "window/KeyCode.hh"
#include "events/KeyEvent.hh"
#include "events/MouseEvent.hh"
#include "events/AppEvent.hh"

#include "graphics/Renderer/Renderer.hh"
#include "graphics/Renderer/Renderer2D.hh"
#include "graphics/Renderer/RenderCommand.hh"
#include "graphics/Renderer/FrameBuffer.hh"
#include "graphics/Common/Shader.hh"
#include "graphics/Common/VertexArray.hh"
#include "graphics/Common/Buffers.hh"
#include "graphics/Common/Cameras.hh"
#include "graphics/Common/CameraControllers.hh"
#include "graphics/Common/Texture.hh"

#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"

#include <imgui.h>
