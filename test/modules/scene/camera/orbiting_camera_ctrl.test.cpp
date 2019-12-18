#include <test.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/scene/camera/orbiting_camera_ctrl.hpp>

using namespace glbr;
using namespace glbr::core;
using namespace glbr::input;
using namespace glbr::renderer;
using namespace glbr::scene;

static const constexpr double TOLERANCE = 0.001;

class DummyGraphicsWindow : public GraphicsWindow {
public:
    std::unique_ptr<EventHandlerRegistration> registerHandler(const EventHandlingFN& fn) override { assert(false); }
    KeyState keyState(KeyCode code) const override { assert(false); }
    KeyState mouseButtonState(MouseButtonCode code) const override { assert(false); }
    Position mousePosition() const override { return {0, 0}; }

    void makeContextCurrent() const override {}
    Context& context() const override { assert(false); }

    Size2D<int> size() const override { return {100, 100}; }
    float pixelRatio() const override { return 1; }
    void run(const RenderFN& onRenderFrame) override {}
    void run(const RenderFN& onRenderFrame, const UpdateFN& onUpdateFrame, double updateRate) override {}
    void close() override {}
};

TEST(OrbitingCameraController, Initialization) {
    DummyGraphicsWindow window{};
    Camera camera{glm::vec3(0, 0, -1)};

    OrbitingCameraController ctrl{camera, window};

    ASSERT_EQ(camera.position(), glm::vec3(0, 0, -1));
    ASSERT_LT(glm::distance(ctrl.target(), glm::vec3(0, 0, 0)), TOLERANCE);
    ASSERT_LT(glm::distance(camera.front(), glm::vec3(0, 0, 1)), TOLERANCE);
}

TEST(OrbitingCameraController, ResetRotation) {
    DummyGraphicsWindow window{};
    Camera camera{glm::vec3(0, 0, -1)};

    auto target = glm::vec3(0, 0, 0);
    OrbitingCameraController ctrl{camera, window, target};

    auto startPosition = camera.position();
    auto startFront = camera.front();

    logging::info("Camera : {}", camera.str());

    // Rotate 90 degrees in 2 axis twice, reset and compare
    ctrl.rotateBy(2 * M_PI, 2 * M_PI);
    ctrl.rotateBy(2 * M_PI, 2 * M_PI);
    ctrl.rotation(0, 0);
    logging::info("Camera : {}", camera.str());
    ASSERT_LT(glm::distance(camera.position(), startPosition), TOLERANCE);
    ASSERT_LT(glm::distance(ctrl.target(), target), TOLERANCE);
    ASSERT_LT(glm::distance(camera.front(), startFront), TOLERANCE);
}

TEST(OrbitingCameraController, RotationYAroundOrigin) {
    DummyGraphicsWindow window{};
    Camera camera{glm::vec3(0, 0, 2)};

    auto target = glm::vec3(0, 0, 0);
    OrbitingCameraController ctrl{camera, window, target};

    auto startPosition = camera.position();
    auto startFront = camera.front();

    logging::info("Camera : {}", camera.str());

    // Rotate 360 and compare
    ctrl.rotateBy(0, 2 * M_PI);
    logging::info("Camera : {}", camera.str());
    ASSERT_LT(glm::distance(camera.position(), startPosition), TOLERANCE);
    ASSERT_LT(glm::distance(ctrl.target(), target), TOLERANCE);
    ASSERT_LT(glm::distance(camera.front(), startFront), TOLERANCE);

    // Rotate 90 degrees ccw around the y axis
    ctrl.rotateBy(0, M_PI / 2.);
    logging::info("Camera : {}", camera.str());
    ASSERT_LT(glm::distance(camera.position(), glm::vec3(2, 0, 0)), TOLERANCE);
    ASSERT_LT(glm::distance(ctrl.target(), target), TOLERANCE);
    ASSERT_LT(glm::distance(camera.front(), glm::vec3(-1, 0, 0)), TOLERANCE);

    // Rotate another 90 degrees ccw around the y axis
    ctrl.rotateBy(0, M_PI / 2.);
    logging::info("Camera : {}", camera.str());
    ASSERT_LT(glm::distance(camera.position(), glm::vec3(0, 0, -2)), TOLERANCE);
    ASSERT_LT(glm::distance(ctrl.target(), target), TOLERANCE);
    ASSERT_LT(glm::distance(camera.front(), glm::vec3(0, 0, 1)), TOLERANCE);

    // Rotate 180 degrees ccw around the y axis to get back home
    ctrl.rotateBy(0, M_PI);
    logging::info("Camera : {}", camera.str());
    ASSERT_LT(glm::distance(camera.position(), startPosition), TOLERANCE);
    ASSERT_LT(glm::distance(ctrl.target(), target), TOLERANCE);
    ASSERT_LT(glm::distance(camera.front(), startFront), TOLERANCE);
}
