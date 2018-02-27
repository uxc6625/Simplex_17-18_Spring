#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	m_pMesh->GenerateCone(2.0f, 5.0f, 3, C_WHITE);
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	
	
	matrix4 m_m4ModelX = glm::rotate(IDENTITY_M4, m_v3Rotation.x, vector3(1.0f, 0.0f, 0.0f));
	matrix4 m_m4ModelY = glm::rotate(IDENTITY_M4, m_v3Rotation.y, vector3(0.0f, 1.0f, 0.0f));
	matrix4 m_m4ModelZ = glm::rotate(IDENTITY_M4, m_v3Rotation.z, vector3(0.0f, 0.0f, 1.0f));

	m_m4Rotation = m_m4ModelX * m_m4ModelY * m_m4ModelZ;
	//matrix4 m_m4Hold;
	//m_m4Hold = ToMatrix4(m_qOrientation) * m_m4Rotation;
	//m_qOrientation = quaternion(matrix4(m_m4Hold));
	


    m_m4Model = glm::toMat4(m_qOrientation);

	
	

	m_pMesh->Render(m4Projection, m4View, m_m4Model);
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
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
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}