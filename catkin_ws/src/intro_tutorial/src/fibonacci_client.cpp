#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <intro_tutorial/FibonacciAction.h>

void doneCb(const actionlib::SimpleClientGoalState &state, const intro_tutorial::FibonacciResultConstPtr &result) {}

void activeCb() {}

void feedbackCb(const intro_tutorial::FibonacciFeedbackConstPtr &feedback)
{
    std::stringstream ss;
    ss << "Received feedback array: [";

    for (size_t i = 0; i < feedback->sequence.size(); ++i)
    {
        ss << feedback->sequence[i];
        if (i < feedback->sequence.size() - 1)
        {
            ss << ", ";
        }
    }

    ss << "]";

    ROS_INFO("%s", ss.str().c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_fibonacci");
    actionlib::SimpleActionClient<intro_tutorial::FibonacciAction> ac("fibonacci", true);
    ROS_INFO("Waiting for action server to start.");

    ac.waitForServer(); // will wait for infinite time
    ROS_INFO("Action server started, sending goal.");

    intro_tutorial::FibonacciGoal goal;
    goal.order = 20;
    ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
    if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s", state.toString().c_str());
    }
    else
        ROS_INFO("Action did not finish before the time out.");

    return 0;
}
