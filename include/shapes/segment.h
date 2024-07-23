#pragma once

#include <FastLED.h>
#include <vector>

class Segment {
private:
    std::vector<CRGB> colours;
    int currentColour;
    int segmentID;
    int start;
    int progress;
    double gradientDuration;
    void fillSegment(CRGB colour);

public:
    Segment(int _segmentID, std::vector<CRGB> _colours, int _startIndex);
    void update();
};