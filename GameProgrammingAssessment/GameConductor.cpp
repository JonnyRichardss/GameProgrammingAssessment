#include "GameConductor.h"
using namespace std::chrono_literals;
static GameConductor* _instance;
GameConductor* GameConductor::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameConductor();
    return _instance;
}
double GameConductor::GetInputTiming(std::chrono::high_resolution_clock::time_point inputTP)
{
    std::chrono::high_resolution_clock::duration epoch_duration = inputTP - firstBeat;
    auto modBeatLength = epoch_duration % beatLength;
    if (modBeatLength > beatLength / 2) {
        return std::chrono::duration_cast<std::chrono::milliseconds>((beatLength - modBeatLength)).count();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(modBeatLength).count();
}
GameConductor::GameConductor()
{
    beatLength = std::chrono::duration_cast<std::chrono::nanoseconds>( 1s / MUSIC_TEMPO);
    firstBeat = std::chrono::high_resolution_clock::now();

}
GameConductor::~GameConductor()
{
}
