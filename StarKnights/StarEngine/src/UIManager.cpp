#include <Engine.hpp>
#include <Bitmap.hpp>
#include <Texture.hpp>
#include <GL/GLTexture.hpp>
#include <MeshData.hpp>
#include <ShaderProgram.hpp>
#include <imgui.h>
#include <iostream>
#include <MenuItem.hpp>
#include <Window.hpp>
#include "UIManager.hpp"

UIManager::UIManager(const Engine& engine)
	: _engine(engine)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformName = "custom_micro_engine";

	//io.KeyMap[ImGuiKey_Tab] = static_cast<size_t>();

	io.RenderDrawListsFn = nullptr;

	int width = 0;
	int height = 0;
	unsigned char* dataPtr;
	io.Fonts->GetTexDataAsRGBA32(&dataPtr, &width, &height);
	uint64_t size = static_cast<uint64_t>(width) * static_cast<uint64_t>(height) * 4;
	std::vector<unsigned char> image(dataPtr, dataPtr + size);

	Bitmap bitmap(4, std::move(image), glm::vec2{ width, height });

	_command.program = _engine.renderer().createProgram("draw");

	_textureUniform = _command.program->createTextureUniform("uTexture");
	_textureUniform->texture = _engine.renderer().createTexture(std::move(bitmap));

	_screenSizeUniform = _command.program->createVec2Uniform("uScreenSize");
	_transformUniform = _command.program->createMat3Uniform("uTransform");

	_command.uniforms.push_back(_transformUniform);
	_command.uniforms.push_back(_screenSizeUniform);
	_command.uniforms.push_back(_textureUniform);
}

void UIManager::visit()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(_engine.window().getWidth()), static_cast<float>(_engine.window().getHeight()));

	io.MousePos = { _mousePos.x, _mousePos.y };

	io.MouseDown[0] = _lMousePressed;
	io.MouseDown[1] = _rMousePressed;
	io.MouseDown[2] = _mMousePressed;

	io.MouseWheel = _mouseWheel;
	_mouseWheel = 0.0f;

	ImGui::NewFrame();

	//ImGui::ShowDemoWindow(&_show_demo_window);
	if (_show_menu)
	{
		for (auto& item : _menuItems)
		{
			item->visit();
		}
	}
	ImGui::Render();

	auto drawData = ImGui::GetDrawData();

	static_assert(sizeof(MeshData::Vertex) == sizeof(ImDrawVert));
	static_assert(sizeof(MeshData::Vertex::position) == sizeof(ImDrawVert::pos));
	static_assert(sizeof(MeshData::Vertex::texcoord) == sizeof(ImDrawVert::uv));
	static_assert(sizeof(MeshData::Vertex::color) == sizeof(ImDrawVert::col));
	static_assert(offsetof(MeshData::Vertex, position) == offsetof(ImDrawVert, pos));
	static_assert(offsetof(MeshData::Vertex, texcoord) == offsetof(ImDrawVert, uv));
	static_assert(offsetof(MeshData::Vertex, color) == offsetof(ImDrawVert, col));

	for (int n = 0; n < drawData->CmdListsCount; ++n)
	{
		const ImDrawList* cmd_list = drawData->CmdLists[n];

		auto vertex_data = reinterpret_cast<MeshData::Vertex*>(cmd_list->VtxBuffer.Data);
		size_t vert_count = static_cast<size_t>(cmd_list->VtxBuffer.size());

		const uint32_t* indexes = cmd_list->IdxBuffer.Data;
		size_t index_count = static_cast<size_t>(cmd_list->IdxBuffer.size());

		MeshData meshData;
		meshData.vertices = { vertex_data, vertex_data + vert_count };
		meshData.indexes = { indexes, indexes + index_count };

		auto vertexBuffer = _engine.renderer().createVertexBuffer(std::move(meshData));

		_command.vertexBuffer = std::move(vertexBuffer);

		_screenSizeUniform->value.x = static_cast<float>(_engine.window().getWidth());
		_screenSizeUniform->value.y = static_cast<float>(_engine.window().getHeight());

		_transformUniform->value = glm::mat3(1.0);

		size_t offset = 0;
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

			_command.ren.emplace();
			_command.ren->count = pcmd->ElemCount;
			_command.ren->offset = static_cast<int>(offset * sizeof(std::uint32_t));

			_command.scissor = glm::vec4(pcmd->ClipRect.x, pcmd->ClipRect.y, pcmd->ClipRect.z, pcmd->ClipRect.w);

			_engine.renderer().addCommand(_command);

			offset += pcmd->ElemCount;
		}
	}
}

void UIManager::handle_event(MouseEvent me)
{
	if (me.type == Action::Down)
	{
		switch (me.button)
		{
		case MouseButton::Left: _lMousePressed = true; break;
		case MouseButton::Right: _rMousePressed = true; break;
		case MouseButton::Middle: _mMousePressed = true; break;
		}
	}
	else
	{
		switch (me.button)
		{
		case MouseButton::Left: _lMousePressed = false; break;
		case MouseButton::Right: _rMousePressed = false; break;
		case MouseButton::Middle: _mMousePressed = false; break;
		}
	}
	_mousePos = me.pos;
}

void UIManager::handle_event(TextInputEvent e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddInputCharactersUTF8(e.string.data());
}

void UIManager::handle_event(MouseWheelEvent e)
{
	if (e.value > 0)
	{
		_mouseWheel = 1;
	}
	if (e.value < 0)
	{
		_mouseWheel = -1;
	}
}

void UIManager::addMenuItem(std::shared_ptr<Menu::MenuItem> item)
{
	_menuItems.push_back(std::move(item));
}

void UIManager::removeMenuItem(const std::shared_ptr<Menu::MenuItem>& item)
{
	auto it = std::find(_menuItems.begin(), _menuItems.end(), item);
	_menuItems.erase(it);
}

void UIManager::handle_event(KeyEvent ev)
{
	if (ev.key == utils::KeyCode::ESCAPE && ev.type == Action::Up)
	{
		_show_menu = !_show_menu;
	}
}