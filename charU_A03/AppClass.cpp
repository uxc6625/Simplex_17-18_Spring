#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits
	float fRadius = 0.95f;
	
	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager
		
		if (fRadius == 0.95f) {

			stopList.push_back(vector3(1,0,0));
			stopList.push_back(vector3(-0.50, .75, 0));
			stopList.push_back(vector3(-0.50, -0.75, 0));
			

		}

		if (fRadius == 1.0f) {
			stopList2.push_back(vector3(1.5, 0, 0));
			stopList2.push_back(vector3(0, 1.5, 0));
			stopList2.push_back(vector3(-1.5, 0, 0));
			stopList2.push_back(vector3(0, -1.5, 0));


		}

		if (fRadius == 1.0f) {
			stopList3.push_back(vector3(2.0, 0, 0));
			stopList3.push_back(vector3(.6, 1.9f, 0));
			stopList3.push_back(vector3(-1.6, 1.2, 0));
			stopList3.push_back(vector3(-1.6, -1.1, 0));
			stopList3.push_back(vector3(0.6, -1.9, 0));


		}

		if (fRadius == 1.5f) {
			stopList4.push_back(vector3(2.5, 0, 0));
			stopList4.push_back(vector3(1.2, 2.1f, 0));
			stopList4.push_back(vector3(-1.3, 2.1, 0));
			stopList4.push_back(vector3(-2.5, 0, 0));
			stopList4.push_back(vector3(-1.3, -2.1, 0));
			stopList4.push_back(vector3(1.2, -2.1, 0));

		}

		if (fRadius == 2.0f) {
			stopList5.push_back(vector3(3.0, 0, 0));
			stopList5.push_back(vector3(1.8, 2.3f, 0));
			stopList5.push_back(vector3(-.7, 2.9, 0));
			stopList5.push_back(vector3(-2.7, 1.3, 0));
			stopList5.push_back(vector3(-2.7, -1.3, 0));
			stopList5.push_back(vector3(-.7, -2.9, 0));
			stopList5.push_back(vector3(1.8, -2.3, 0));
		}

		if (fRadius == 2.5f) {
			stopList6.push_back(vector3(3.5, 0, 0));
			stopList6.push_back(vector3(2.4, 2.5f, 0));
			stopList6.push_back(vector3(0, 3.5, 0));
			stopList6.push_back(vector3(-2.4, 2.5, 0));
			stopList6.push_back(vector3(-3.5, 0, 0));
			stopList6.push_back(vector3(-2.4, -2.5, 0));
			stopList6.push_back(vector3(0, -3.5, 0));
			stopList6.push_back(vector3(2.4, -2.5, 0));
		}

		if (fRadius == 3.0f) {
			stopList7.push_back(vector3(4.0, 0, 0));
			stopList7.push_back(vector3(3.0, 2.6f, 0));
			stopList7.push_back(vector3(0.7, 3.9, 0));
			stopList7.push_back(vector3(-2.0, 3.4, 0));
			stopList7.push_back(vector3(-3.7, 1.3, 0));
			stopList7.push_back(vector3(-3.7, -1.3, 0));
			stopList7.push_back(vector3(-2.0, -3.4, 0));
			stopList7.push_back(vector3(0.7, -3.9, 0));
			stopList7.push_back(vector3(3.0, -2.6f, 0));
		}

		
		
		
		fSize += 0.5f; //increment the size for the next orbit
		fRadius = fSize - 0.5f; //increment the radius
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Get a timer
    static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer


	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	m4Offset = glm::rotate(IDENTITY_M4, 90.0f, AXIS_Z);

	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i)
	{
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 90.0f, AXIS_X));
		static uint path = 0; //current route
		static uint path2 = 0;
		static uint path3 = 0;
		static uint path4 = 0;
		static uint path5 = 0;
		static uint path6 = 0;
		static uint path7 = 0;
	
		v3Start = stopList[path]; //start at the current route
		v3End = stopList[(path + 1) % stopList.size()]; //end at route 
		v3CurrentPos = glm::lerp(v3Start, v3End, fTimer);

		v3Start2 = stopList2[path2]; //start at the current route
		v3End2 = stopList2[(path2 + 1) % stopList2.size()]; //end at route 
		v3CurrentPos2 = glm::lerp(v3Start2, v3End2, fTimer);

		v3Start3 = stopList3[path3]; //start at the current route
		v3End3 = stopList3[(path3 + 1) % stopList3.size()]; //end at route 
		v3CurrentPos3 = glm::lerp(v3Start3, v3End3, fTimer);

		v3Start4 = stopList4[path4]; //start at the current route
		v3End4 = stopList4[(path4 + 1) % stopList4.size()]; //end at route 
		v3CurrentPos4 = glm::lerp(v3Start4, v3End4, fTimer);

		v3Start5 = stopList5[path5]; //start at the current route
		v3End5 = stopList5[(path5 + 1) % stopList5.size()]; //end at route 
		v3CurrentPos5 = glm::lerp(v3Start5, v3End5, fTimer);

		v3Start6 = stopList6[path6]; //start at the current route
		v3End6 = stopList6[(path6 + 1) % stopList6.size()]; //end at route 
		v3CurrentPos6 = glm::lerp(v3Start6, v3End6, fTimer);

		v3Start7 = stopList7[path7]; //start at the current route
		v3End7 = stopList7[(path7 + 1) % stopList7.size()]; //end at route 
		v3CurrentPos7 = glm::lerp(v3Start7, v3End7, fTimer);

		if (fTimer >= 1.0f)
		{
			path++;//go to the next route
			path2++;
			path3++;
			path4++;
			path5++;
			path6++;
			path7++;
			fTimer = m_pSystem->GetDeltaTime(uClock);//restart the clock
			path %= stopList.size();
			path2 %= stopList2.size();
			path3 %= stopList3.size();
			path4 %= stopList4.size();
			path5 %= stopList5.size();
			path6 %= stopList6.size();
			path7 %= stopList7.size();
		}

		matrix4 m4Model = glm::translate(m4Offset, v3CurrentPos);
		matrix4 m4Model2 = glm::translate(m4Offset, v3CurrentPos2);
		matrix4 m4Model3 = glm::translate(m4Offset, v3CurrentPos3);
		matrix4 m4Model4 = glm::translate(m4Offset, v3CurrentPos4);
		matrix4 m4Model5 = glm::translate(m4Offset, v3CurrentPos5);
		matrix4 m4Model6 = glm::translate(m4Offset, v3CurrentPos6);
		matrix4 m4Model7 = glm::translate(m4Offset, v3CurrentPos7);

		

		//draw spheres
		
			m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.2)), C_WHITE);
			m_pMeshMngr->AddSphereToRenderList(m4Model2 * glm::scale(vector3(0.2)), C_WHITE);
			m_pMeshMngr->AddSphereToRenderList(m4Model3 * glm::scale(vector3(0.2)), C_WHITE);
			m_pMeshMngr->AddSphereToRenderList(m4Model4 * glm::scale(vector3(0.2)), C_WHITE);
			m_pMeshMngr->AddSphereToRenderList(m4Model5 * glm::scale(vector3(0.2)), C_WHITE);
			m_pMeshMngr->AddSphereToRenderList(m4Model6 * glm::scale(vector3(0.2)), C_WHITE);
			m_pMeshMngr->AddSphereToRenderList(m4Model7 * glm::scale(vector3(0.2)), C_WHITE);
		
	}

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}