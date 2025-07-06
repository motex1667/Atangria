template<typename S, typename D>
using SegueType = ata::Controller::segue<S, D>;

template<typename M, typename S, typename D, typename ... Args>
int Application::run(Args&& ... args)
{
    static_assert(!ata::Controller::IsSegueType<M>::value, "Main state cannot be of Segue Type");
    ata::StopWatch timer;
    float elapsed = 0.f;
    ata::Renderer::pushStates();
    m_controller.push<typename SegueType<S, D>::template to<M>>(std::forward<Args>(args)...);
    while(m_controller.getSurface()->isRunning())
    {
        timer.reset();
        ata::pollEvents();
        m_controller.update(elapsed);
        m_controller.draw();
        m_controller.getSurface()->swapBuffers();
        elapsed = static_cast<float>(ata::asSeconds(timer.getElapsed()));
    }
	ata::Renderer::popStates();
	
    return 0;
}
