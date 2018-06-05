#pragma once

struct NoiseParameters
{
    int octaves;
    int amplitude;
    int smoothness;
    int heightOffset;

    double roughness;
};

class NoiseGenerator
{
    public:
        NoiseGenerator(int seed);

        double getHeight(int x, int z);

        void setParameters(const NoiseParameters& params);

    private:
        double getNoise(int  n);
        double getNoise(double  x, double  z);

        double lerp(double a, double b, double z);

        double noise(double  x, double  z);

        NoiseParameters m_noiseParameters;

        int m_seed;
};
