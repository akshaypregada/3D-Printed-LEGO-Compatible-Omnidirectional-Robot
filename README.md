# 3D-Printed-LEGO-Compatible-Omnidirectional-Robot

🛠️ How to Run This Setup

1️⃣ Upload ESP32 Code
Flash omnidirectional_robot.ino to ESP32.
Connect ESP32 to your WiFi.

2️⃣ Setup SSH on ESP32
- Install an SSH server on your Raspberry Pi (if needed):
sudo apt update
sudo apt install openssh-server

- Enable SSH
sudo systemctl enable ssh
sudo systemctl start ssh

3️⃣ Run ROS Node
- Launch SSH-based ROS controller:
roslaunch your_package robot_launch.launch

- Send movement commands manually:
rostopic pub /robot_movement std_msgs/String "forward"

4️⃣ Access Web UI
- Open a browser and navigate to:
http://ESP32_IP_ADDRESS/

🚀 Summary
ESP32 controls motors and hosts a web-based control interface.
ROS integrates SSH control, allowing remote execution.
SSH enables secure communication between ROS and ESP32.
Web-based UI provides user-friendly control.
GitHub repository setup for easy sharing and future improvements.
