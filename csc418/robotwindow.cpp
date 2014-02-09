#include "robotwindow.h"

// Robot
#define BODY_POSITION_MIN -30.0f
#define BODY_POSITION_MAX  30.0f
#define JOINT_ANGLE_MIN -45.0f
#define JOINT_ANGLE_MAX  45.0f
#define JOINT_SCALE_MIN 0.5f
#define JOINT_SCALE_MAX 3.0f
#define ANIMATE_SPEED 0.1
#define ROBOT_UNIT 30

void checkboxTrigger(int id) {
    cout << id << endl;
}

void quitButton(int) {
    exit(0);
}

Circ::Circ(const char* name, float rad, Vector3 col,
     Vector3 p, Vector3 s, Vector3 r):
    Object(name, p, s, r),
    color(col)
{
    radius = rad;
}

void Circ::render() {
    float i;
    float inc = 2*PI/radius;
    // float inc = 0.1;
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 2*PI; i+=inc) {
        glVertex2f(radius*cos(i), radius*sin(i));
    }
    glEnd();
}

void Circ::update() {

}

Rect::Rect(const char* name, float x, float y,
               Vector3 col, Vector3 p, Vector3 s, Vector3 r):
    Object(name, p, s, r),
    color(col)
{
    sx = x;
    sy = y;
}

void Rect::render() {
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_QUADS);
    glVertex2f(-sx/2, -sy/2);
    glVertex2f(sx/2, -sy/2);
    glVertex2f(sx/2, sy/2);
    glVertex2f(-sx/2, sy/2);
    glEnd();
}

void Rect::update() {

}

// Robot Arms

RobotLimb::RobotLimb(const char* name, Vector3 col,
                   Vector3 position, Vector3 h, Vector3 rotation):
    Rect(name, 3*ROBOT_UNIT, ROBOT_UNIT, col,
         position, ajMath::One, rotation),
    joint("Joint", 6, Vector3(0.0, 0.0, 0.0),
          Vector3(ROBOT_UNIT, 0, 0)),
    hinge(h)
{
    angle = 0.0f;
    posx = position.x;
    extend = 1.0f;
    attachChild(&joint);
}


void RobotLimb::render() {
    Rect::render();
}

void RobotLimb::update() {
    rotateAround(hinge, Vector3(0,0,1), angle);
    pos.x = posx - (extend-1)*sx/2;
    scale.x = extend;
}

// Robot Head

RobotHead::RobotHead(const char* name, Vector3 col, Vector3 pos) :
    Rect(name, 6*ROBOT_UNIT, 4*ROBOT_UNIT, col, pos),
    leyeOut("Left Eye Outer", 22, Vector3(0,0,0), Vector3(-1.5*ROBOT_UNIT, 0,0)),
    leyeIn("Left Eye Inner", 20, Vector3(0,0,0), Vector3(-1.5*ROBOT_UNIT, 0,0)),
    reyeOut("Right Eye Outer", 22, Vector3(0,0,0), Vector3(1.5*ROBOT_UNIT, 0,0)),
    reyeIn("Right Eye Inner", 20, Vector3(0,0,0), Vector3(1.5*ROBOT_UNIT, 0,0))
{
    attachChild(&leyeOut);
    attachChild(&leyeIn);
    attachChild(&reyeOut);
    attachChild(&reyeIn);
}

void RobotHead::render()
{
    Rect::render();
}

// Robot Window

const char robotname[] = "RobotWindow";

RobotWindow::RobotWindow():
    Window(10, 10, 480, 640, robotname),
    body("Robot Body", 3*ROBOT_UNIT, 4*ROBOT_UNIT,
         Vector3(1, 1, 1)),
    hips("Robot Hips", 5*ROBOT_UNIT, ROBOT_UNIT,
         Vector3(1, 1, 1), Vector3(0.0, -2.5*ROBOT_UNIT, 0)),
    neck("Robot Neck", Vector3(0, 0.5, 0.7), Vector3(0.0, 2.5*ROBOT_UNIT, 0),
         Vector3(0, 1.5*ROBOT_UNIT, 0), Vector3(0,0,-90)),
    head("Robot Head", Vector3(0, 0.6, 0.7), Vector3(-2*ROBOT_UNIT, 0, 0)),
    larm("Robot Left Arm", Vector3(1.0, 0, 0),
         Vector3(-2*ROBOT_UNIT, ROBOT_UNIT/2, 0), Vector3(-ROBOT_UNIT, 0, 0)),
    rarm("Robot Right Arm", Vector3(1.0, 0.0, 0.0),
         Vector3(2*ROBOT_UNIT, ROBOT_UNIT/2, 0), Vector3(ROBOT_UNIT, 0, 0),
         Vector3(0,0,180)),
    lhand("Robot Left Hand", Vector3(0.0, 1.0, 0.0),
         Vector3(-2*ROBOT_UNIT, 0, 0), Vector3(-ROBOT_UNIT, 0, 0)),
    rhand("Robot Right Hand", Vector3(0.0, 1.0, 0.0),
         Vector3(-2*ROBOT_UNIT, 0, 0), Vector3(-ROBOT_UNIT, 0, 0)),
    lleg("Robot Left Leg", Vector3(1.0, 0.0, 0.0),
         Vector3(-2*ROBOT_UNIT, -ROBOT_UNIT, 0),
         Vector3(-2*ROBOT_UNIT, 0, 0), Vector3(0,0,90)),
    rleg("Robot Right Leg", Vector3(1.0, 0.0, 0.0),
         Vector3(2*ROBOT_UNIT, -ROBOT_UNIT, 0),
         Vector3(2*ROBOT_UNIT, 0, 0), Vector3(0,0,90))

{
    attachObject(&body);
    body.attachChild(&larm);
    body.attachChild(&rarm);
    body.attachChild(&hips);
    body.attachChild(&neck);
    larm.attachChild(&lhand);
    rarm.attachChild(&rhand);
    hips.attachChild(&lleg);
    hips.attachChild(&rleg);
    neck.attachChild(&head);

    // this is because the neck is a rotated arm
    head.rot.z = 90;

    GLUI_Master.set_glutIdleFunc(NULL);

    // Create GLUI window
    controls = GLUI_Master.create_glui("Controls", 0, 500, 0);

    GLUI_Spinner *joint_spinner;
    joint_spinner = controls->add_spinner("Vertical Body Position",
                                          GLUI_SPINNER_FLOAT, &(body.pos.y));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(BODY_POSITION_MIN,
                                    BODY_POSITION_MAX, GLUI_LIMIT_CLAMP);

    // add control for neck/head
    joint_spinner = controls->add_spinner("Robot Head",
                                          GLUI_SPINNER_FLOAT, &(neck.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    controls->add_separator();

    // add control for left arm
    joint_spinner = controls->add_spinner("Left Arm Angle",
                                          GLUI_SPINNER_FLOAT, &(larm.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    // control for right arm
    joint_spinner = controls->add_spinner("Right Arm Angle",
                                          GLUI_SPINNER_FLOAT, &(rarm.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    controls->add_separator();

    // left and right hand angle controls
    joint_spinner = controls->add_spinner("Left Hand Angle",
                                          GLUI_SPINNER_FLOAT, &(lhand.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    joint_spinner = controls->add_spinner("Right Hand Angle",
                                          GLUI_SPINNER_FLOAT, &(rhand.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    controls->add_column(true);

    // left and right scale controls
    joint_spinner = controls->add_spinner("Left Hand Scale",
                                          GLUI_SPINNER_FLOAT, &(lhand.extend));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_SCALE_MIN,
                                    JOINT_SCALE_MAX, GLUI_LIMIT_CLAMP);

    joint_spinner = controls->add_spinner("Right Hand Scale",
                                          GLUI_SPINNER_FLOAT, &(rhand.extend));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_SCALE_MIN,
                                    JOINT_SCALE_MAX, GLUI_LIMIT_CLAMP);

    controls->add_separator();

    // left and right legs angle controls
    joint_spinner = controls->add_spinner("Left Leg Angle",
                                          GLUI_SPINNER_FLOAT, &(lleg.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    joint_spinner = controls->add_spinner("Right Leg Angle",
                                          GLUI_SPINNER_FLOAT, &(rleg.angle));
    joint_spinner->set_speed(ANIMATE_SPEED);
    joint_spinner->set_float_limits(JOINT_ANGLE_MIN,
                                    JOINT_ANGLE_MAX, GLUI_LIMIT_CLAMP);

    controls->add_column(true);
    controls->add_checkbox("Animate", &idleUpdate, getId(), setIdleUpdate);

    controls->add_separator();
    controls->add_button("Quit", 0, quitButton);

    controls->set_main_gfx_window(getId());

    display(); // render at least once
}

void RobotWindow::update() {
    if (idleUpdate) {
        // cout << "Update!" << endl;
        body.pos.y = BODY_POSITION_MAX*sin(animateCounter*ANIMATE_SPEED);
        neck.angle = JOINT_ANGLE_MAX*sin(2*animateCounter*ANIMATE_SPEED);
        larm.angle = JOINT_ANGLE_MAX*sin(3*animateCounter*ANIMATE_SPEED);
        rarm.angle = JOINT_ANGLE_MAX*sin(2*animateCounter*ANIMATE_SPEED);
        rhand.angle = JOINT_ANGLE_MAX*sin(3*animateCounter*ANIMATE_SPEED);
        lhand.angle = JOINT_ANGLE_MAX*sin(4*animateCounter*ANIMATE_SPEED);
        lleg.angle = JOINT_ANGLE_MAX*sin(animateCounter*ANIMATE_SPEED);
        rleg.angle = JOINT_ANGLE_MAX*sin(2*animateCounter*ANIMATE_SPEED);

        rhand.extend = (JOINT_SCALE_MAX - JOINT_SCALE_MIN)*
                sin(5*animateCounter*ANIMATE_SPEED)/2 + (JOINT_SCALE_MAX + JOINT_SCALE_MIN)/2;
        lhand.extend = (JOINT_SCALE_MAX - JOINT_SCALE_MIN)*
                sin(2*animateCounter*ANIMATE_SPEED)/2 + (JOINT_SCALE_MAX + JOINT_SCALE_MIN)/2;

        controls->sync_live();

        animateCounter++;
    }else {
        animateCounter = 0;
    }
}
