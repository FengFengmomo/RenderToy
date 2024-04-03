/*
* Class:
*	Light
* Description:
*	This class contains all light sources in the scene
*/

#pragma once

#include "core/Core.h"
#include "Point.h"
#include "Spot.h"
#include "Directional.h"

enum LightType
{
	POINT_LIGHT,
	SPOT_LIGHT,
	DIRECTIONAL_LIGHT
};

class Light
{
private:
	std::map<std::string, Point> m_Points;
	std::vector<std::string> m_PointList;
	std::map<std::string, Spot> m_Spots;
	std::vector<std::string> m_SpotList;
	std::map<std::string, Directional> m_Directionals;
	std::vector<std::string> m_DirectionalList;

	void AddPoint(std::string name);
	void AddSpot(std::string name);
	void AddDirectional(std::string name);

public:
	Light();
	~Light();

	void Init();

	void AddLight(std::string name, LightType lightType);
	

	// Get Light's members
	std::map<std::string, Point>& GetPoints();
	std::vector<std::string>& GetPointList();
	std::map<std::string, Spot>& GetSpots();
	std::vector<std::string>& GetSpotList();
	std::map<std::string, Directional>& GetDirectionals();
	std::vector<std::string>& GetDirectionalList();

	// Get Light's UI
	void GetUI();
};

