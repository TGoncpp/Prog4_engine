#pragma once
#include "imgui_plot.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>


struct transform
{
    float matrix[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
};

class GameObject final
{
public:
    transform local{};
    int id{ 5 };

    GameObject& operator*=(int other)
    {
        id *= other;
        return *this;
    }
};


class CacheExercice final
{
public:
	static void TrashTheCache( );

private:
    inline static ImGui::PlotConfig PlotConfig{};
	static const int M_NUM_OF_STEPSIZESFFER_SIZE{ 11 };
    inline static bool m_IsDirtyInt{ false };
    inline static bool m_IsDirtyOB{ false };
    static const int M_BUFFER_SIZE{ 1000000 };
	inline static int m_BufferOfInts[M_BUFFER_SIZE]{};
    inline static GameObject m_BufferOfGO[M_BUFFER_SIZE]{};
    inline static float m_ArrIntResults[M_NUM_OF_STEPSIZESFFER_SIZE] {};
    inline static float m_ArrGOResults[M_NUM_OF_STEPSIZESFFER_SIZE]{};

    static float CalculateAverage(std::vector<float> vector);
    template<typename T>
    static void CalculateAverageLooptimeOfBuffer(T* buffer, int size, float* arrResults, int numOfSamples);

};

float CacheExercice::CalculateAverage(std::vector<float> vector)
{
    auto minMax = std::minmax_element(vector.cbegin(), vector.cend());
    std::pair<float, float> dMinMax = std::make_pair<>(*minMax.first, *minMax.second);

    vector.erase(std::remove_if(vector.begin(), vector.end(), [dMinMax](float e)
        { return   e == dMinMax.first || e == dMinMax.second; }), vector.end());

    return std::accumulate(vector.cbegin(), vector.cend(), 0.0f) / vector.size();
}

template<typename T>
void CacheExercice::CalculateAverageLooptimeOfBuffer(T* buffer, int size, float* arrResults, int numOfSamples)
{
    int resultIndex{};
    std::vector< float> vecStoredTimes(numOfSamples);

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        for (int recordTest = 0; recordTest < numOfSamples; ++recordTest)
        {

            auto start = std::chrono::high_resolution_clock::now();
            for (int i{}; i < size; i += stepsize)
            {
                buffer[i] *= 2;
                buffer[i] *= 2;
                buffer[i] *= 2;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto time = std::chrono::duration<float, std::micro>(end - start);
            vecStoredTimes[recordTest] = time.count();

        }

        arrResults[resultIndex++] = CalculateAverage(vecStoredTimes) ;
    }
}

void CacheExercice::TrashTheCache()
{
    const float xData[] { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f, 552.f, 1024.f };
    static ImU32 red = ImColor(255.f, 0.f, 0.f);
    static ImU32 blue = ImColor(0.f, 0.f, 255.f);

    //Start
    //-----------------------------------------------
    ImGui::Begin("Exercise 2 ", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    //Set Sample amount
    //----------------------------------------------
    static int numOfSamples{ 15 };
    ImGui::InputInt("# samples", &numOfSamples);

    //Trash The int cache
    //--------------------------------------------------
    if (ImGui::Button("Trash the cache with ints"))
        m_IsDirtyInt = true;

    if (m_IsDirtyInt)
    {
        CalculateAverageLooptimeOfBuffer(m_BufferOfInts, M_BUFFER_SIZE, m_ArrIntResults, numOfSamples);
        m_IsDirtyInt = false;
    }

        PlotConfig.values.xs       = xData;
        PlotConfig.values.ys       = m_ArrIntResults;
        PlotConfig.values.count    = M_NUM_OF_STEPSIZESFFER_SIZE;
        PlotConfig.values.color    = red;
        PlotConfig.scale.min       = 0.f;
        PlotConfig.scale.max       = m_ArrIntResults[0];
        PlotConfig.tooltip.show    = true;
        PlotConfig.grid_x.show     = true;
        PlotConfig.grid_x.size     = 1024.f;
        PlotConfig.grid_x.subticks = 10;
        PlotConfig.grid_y.show     = true;
        PlotConfig.grid_y.size     = 10.f;
        PlotConfig.grid_y.subticks = 10;
        PlotConfig.tooltip.format  = "x=%.2f, y=%.2f";
        PlotConfig.frame_size      = ImVec2(400, 400);
        PlotConfig.line_thickness  = 2.f;

         ImGui::Plot("IntBuffer", PlotConfig);
    


    //Trash The gameObj cache
    //--------------------------------------------------
    if (ImGui::Button("Trash the cache with gameObjects"))
        m_IsDirtyOB = true;
    if (m_IsDirtyOB)
    {
        CalculateAverageLooptimeOfBuffer(m_BufferOfGO, M_BUFFER_SIZE, m_ArrGOResults, numOfSamples);
        m_IsDirtyOB = false;
    }
    
    PlotConfig.values.ys        = m_ArrGOResults;
    PlotConfig.scale.max        = m_ArrGOResults[0];
    PlotConfig.values.color     = blue;
    
    ImGui::Plot("GameObjects", PlotConfig);


    //Show combined graphs
    //-----------------------------------------------
    ImGui::SeparatorText("combined");
    const float* YDataList[] = { m_ArrIntResults, m_ArrGOResults };
    ImU32 colors[2]          = {  ImColor(255, 0, 0), ImColor(0, 0, 255) };
    
    PlotConfig.values.ys        = nullptr;
    PlotConfig.values.ys_list   = YDataList;
    PlotConfig.values.ys_count  = 2;
    PlotConfig.values.colors    = colors;
    PlotConfig.scale.max        = m_ArrGOResults[0];
    
    
    ImGui::Plot("Int+Obj", PlotConfig);


    ImGui::End();
}

