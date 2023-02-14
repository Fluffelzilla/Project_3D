#pragma once
#include <d3d11_4.h>
#include <DirectXMath.h>

//#include "ConstantBuffer.h"

//TODO: All rotation info i .cpp är inte sparat i någon variabel eller liknande, detta MÅSTE fixas!!!
//kanske är fixat, måste testas!!!

struct ProjectionInfo
{
	float fovAngleY = 0.4 * 3.14f; //field of view
	float aspectRatio = 1024.0f / 576.0f; //brädden på fönstret * höjden på fönstret
	float nearZ = 0.1f;
	float farZ = 1000.0f;
};

struct MatrixInfo
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX viewPro;
	DirectX::XMFLOAT3 cPosition;
	float pad;
};

class Camera
{
private:
	DirectX::XMFLOAT3 position = { 0.0f, 0.0f, -2.0f };
	DirectX::XMFLOAT3 forward = { 0.0f, 0.0f, 1.0f };
	DirectX::XMFLOAT3 right = { 1.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 up = { 0.0f, 1.0f, 0.0f };
	ProjectionInfo projInfo;
	MatrixInfo matrixInfo;

	ID3D11Buffer* cameraBuffer;

	void MoveInDirection(float amount, const DirectX::XMFLOAT3& direction);
	void RotateAroundAxis(float amount, const DirectX::XMFLOAT3& axis);

public:
	Camera() = default;
	Camera(ID3D11Device* device, const ProjectionInfo& projectionInfo,
		const DirectX::XMFLOAT3& initialPosition = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	~Camera();
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = default;
	Camera& operator=(Camera&& other) = default;

	void Initialize(ID3D11Device* device, const ProjectionInfo& projectionInfo,
		const DirectX::XMFLOAT3& initialPosition = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));

	void InitializeBuffer(ID3D11Device* device);

	void MoveForward(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);

	void RotateForward(float amount);
	void RotateRight(float amount);
	void RotateUp(float amount);

	const DirectX::XMFLOAT3& GetPosition() const;
	const DirectX::XMFLOAT3& GetForward() const;
	const DirectX::XMFLOAT3& GetRight() const;
	const DirectX::XMFLOAT3& GetUp() const;

	void UpdateInternalConstantBuffer(ID3D11DeviceContext* context);
	ID3D11Buffer* GetConstantBuffer() const;

	DirectX::XMFLOAT4X4 GetViewProjectionMatrix() const;
};

