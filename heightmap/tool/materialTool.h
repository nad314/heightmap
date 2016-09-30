#pragma once

class MaterialTool final : public core::EventListener, public core::Getter<MaterialTool> {
private:
	core::glComputeShader compute;
	uint uniform[8];
public:
	MaterialTool();
	~MaterialTool();
};

