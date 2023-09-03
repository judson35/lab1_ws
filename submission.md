# Lab 1: Intro to ROS 2

## Written Questions

### Q1: During this assignment, you've probably ran these two following commands at some point: ```source /opt/ros/foxy/setup.bash``` and ```source install/local_setup.bash```. Functionally what is the difference between the two?

The first command sources your ros environment. This allows you to run all the ros specific commands like ros2 run etc. The second sources your workspace envrironment which provides you with all the package specific commands and executable commands. This allows for tab complete of all the package files etc. Additionaly, the sourcing of the ros environment only has to be done every time a new terminal is opened because we don't change anything in the environmet when building packages. The sourcing of your workspace setup.bash, however does need to be run everytime the workspace is built again. This will add all the new variables and commands into the environment that were changed in the build process.

### Q2: What does the ```queue_size``` argument control when creating a subscriber or a publisher? How does different ```queue_size``` affect how messages are handled?

The queue size argument controls how many messages are stored into a buffer while nodes are reading the messages or publishing new ones. Increasing the queue size allows nodes to read messages from further back in time with the downside of taking up more memory to store those previous messages.

### Q3: Do you have to call ```colcon build``` again after you've changed a launch file in your package? (Hint: consider two cases: calling ```ros2 launch``` in the directory where the launch file is, and calling it when the launch file is installed with the package.)

No colcon build does not need to be called again after changing a launch file but it will need to be called again if you create a new launch file. Calling it again will only add the filename to your environment allowing for tab complete. It is not necessary to do so though.
