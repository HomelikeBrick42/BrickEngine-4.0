#pragma once

#include "pch.h"

class CameraController : public EntityScript
{
public:
	virtual void OnCreate() override
	{
		if (!HasComponent<Transform>())
			AddComponent<Transform>();
		m_Transform = &GetComponent<Transform>();

		if (!HasComponent<Camera>())
			AddComponent<Camera>();
		m_Camera = &GetComponent<Camera>();
		m_Camera->Projection = glm::perspective(glm::radians(70.0f), 1280.0f / 720.0f, 0.001f, 1000.0f);

		m_Front = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Up = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Right = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Pitch = 0.0f;
		m_Yaw = 0.0f;
		m_MoveSpeed = 2.0f;
		m_RotateSpeed = 5.0f;
		m_MouseLocked = true;

		UpdateCameraVectors();

		Input::SetCursorState(m_MouseLocked ? CursorState::Locked : CursorState::Normal);
	}

	virtual void OnUpdate() override
	{
		float dt = Time::GetDelta();
		float speed = Input::GetKey(KeyCode::LeftShift) ? m_MoveSpeed * 5.0f : m_MoveSpeed;

		if (Input::GetKeyDown(KeyCode::Escape))
		{
			m_MouseLocked = !m_MouseLocked;
			Input::SetCursorState(m_MouseLocked ? CursorState::Locked : CursorState::Normal);
		}

		if (m_MouseLocked)
		{
			glm::vec2 mouseDelta = Input::GetMouseDelta();

			m_Pitch -= mouseDelta.y * m_RotateSpeed * dt;
			m_Yaw -= mouseDelta.x * m_RotateSpeed * dt;
		}

		if (Input::GetKey(KeyCode::W))
			m_Transform->Position += m_Front * speed * dt;
		if (Input::GetKey(KeyCode::S))
			m_Transform->Position -= m_Front * speed * dt;
		if (Input::GetKey(KeyCode::A))
			m_Transform->Position -= m_Right * speed * dt;
		if (Input::GetKey(KeyCode::D))
			m_Transform->Position += m_Right * speed * dt;
		if (Input::GetKey(KeyCode::E))
			m_Transform->Position += m_Up * speed * dt;
		if (Input::GetKey(KeyCode::Q))
			m_Transform->Position -= m_Up * speed * dt;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		UpdateCameraVectors();
		m_Transform->Rotation = glm::quatLookAt(m_Front, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	virtual void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent& e)
			{
				m_Camera->Projection = glm::perspective(glm::radians(70.0f), (float)e.GetWidth() / (float)e.GetHeight(), 0.001f, 1000.0f);
				return false;
			});
	}
private:
	void UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
private:
	Transform* m_Transform;
	Camera* m_Camera;
private:
	glm::vec3 m_Front, m_Right, m_Up;
	float m_Pitch, m_Yaw;
	float m_MoveSpeed, m_RotateSpeed;
	bool m_MouseLocked;
};
