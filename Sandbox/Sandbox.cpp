import Mikrokosmos;

#include <Mikrokosmos/Core.h>

class ExampleLayer : public mk::Layer
{

public:

	         ExampleLayer() = default;
	virtual ~ExampleLayer() = default;

	void OnUpdate(float timeStep) override
	{
		mk::info("ExampleLayer::Update");
	}
	
	void OnEvent(mk::Event& event) override
	{
		mk::trace("ExampleLayer::OnEvent");
	}

private:


};

class Sandbox : public mk::Application
{

public:

	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}

	~Sandbox() = default;

private:

};

int main()
{
	auto application = std::make_unique<Sandbox>();

	try
	{
		application->Run();
	}
	catch (const std::exception& exception)
	{
		mk::error(exception.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}