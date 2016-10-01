#pragma once

class MaterialTool final : public core::EventListener, public core::Getter<MaterialTool> {
private:
	core::glComputeShader compute;
	uint uniform[8];
	vec2i mpos;
	vec2i lpos;
	bool drawing = 0;
public:
	MaterialTool();
	~MaterialTool();

	int onPaint(const core::eventInfo& e) override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onMouseMove(const core::eventInfo& e) override;

};

