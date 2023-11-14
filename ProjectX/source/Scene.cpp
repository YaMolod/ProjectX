#include "Scene.h"
#include <bx/timer.h>

Scene::Scene()
{
	Init();
}

Scene::~Scene()
{
	ShutDown();
}

void Scene::Init()
{
	m_program = loadProgram("vs_mesh", "fs_mesh");
	m_mesh = meshLoad("assets/meshes/bunny.bin");
	u_time = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);
	m_timeOffset = bx::getHPCounter();
}

void Scene::ShutDown()
{
	meshUnload(m_mesh);
	bgfx::destroy(m_program);
	bgfx::destroy(u_time);
}

void Scene::OnUpdate()
{
	bgfx::touch(0);

	float time = (float)( (bx::getHPCounter()-m_timeOffset)/double(bx::getHPFrequency() ) );
	bgfx::setUniform(u_time, &time);

	const bx::Vec3 at  = { 0.0f, 1.0f,  0.0f };
	const bx::Vec3 eye = { 0.0f, 1.0f, -2.5f };

	{
		float view[16];
		bx::mtxLookAt(view, eye, at);

		float proj[16];
		bx::mtxProj(proj, 60.0f, float(1280)/float(720), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);

		bgfx::setViewRect(0, 0, 0, uint16_t(1280), uint16_t(720) );
	}

	float mtx[16];
	bx::mtxRotateXY(mtx
		, 0.0f
		, time
		);

	meshSubmit(m_mesh, 0, m_program, mtx);
}
