#include <main/main.h>

MaterialFrame::MaterialButton* core::Getter<MaterialFrame::MaterialButton>::getter = NULL;

MaterialFrame::MaterialButton& MaterialFrame::MaterialButton::make(const core::vec4i& r, Form& f, core::glTextureMaterial *m, core::buttonFunc func) {
	if (!getter)
		set(*this);
	mat = m;

	core::Image i;
	m->diffuse.construct(i);
	Sidebar::adjustImage(i, i, r.z-r.x);
	f.setControlColors(*this);
	ImageButton::make(r, &i, f, func).prerender();
	i.dispose();
	return *this;
}
