#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui_window.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex       = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void TG::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext);
	ImGui_ImplOpenGL3_Init();

}

void TG::Renderer::Render(float) const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	//CacheExercice::TrashTheCache();
	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	SDL_RenderPresent(m_renderer);
}

void TG::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

}

void TG::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, int colum, int row, int currentFrame) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	float scale = texture.GetScale();
	
	
	if (currentFrame > -1)
	{
		SDL_Rect src{};
		src.w = static_cast<int>( dst.w * scale / (colum * scale));
		src.h = static_cast<int>( dst.h  *scale/ (row   * scale));
		src.x = static_cast<int>(src.w * (currentFrame % colum));
		src.y = static_cast<int>(src.h * (currentFrame / colum));

		//rescale to original size off png
		dst.w = static_cast<int>((dst.w * scale) / colum);
		dst.h = static_cast<int>((dst.h * scale) / row);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
		return;
	}
	else
	{
		dst.w = static_cast<int>(dst.w * scale);
		dst.h = static_cast<int>(dst.h * scale);
	}
	
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void TG::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* TG::Renderer::GetSDLRenderer() const { return m_renderer; }
