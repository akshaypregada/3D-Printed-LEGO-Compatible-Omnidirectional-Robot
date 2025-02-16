#!/usr/bin/env python3
import rospy
import paramiko
from std_msgs.msg import String

# SSH Configuration
SSH_HOST = "192.168.X.X"  # ESP32 IP Address
SSH_USER = "pi"  # Change if needed
SSH_PASS = "raspberry"  # Change accordingly

def send_command(command):
    """ Send commands via SSH to the ESP32-based robot """
    try:
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(SSH_HOST, username=SSH_USER, password=SSH_PASS)

        stdin, stdout, stderr = client.exec_command(f"curl http://{SSH_HOST}/{command}")
        response = stdout.read().decode().strip()
        rospy.loginfo(f"Response: {response}")

        client.close()
    except Exception as e:
        rospy.logerr(f"SSH Error: {e}")

def command_callback(msg):
    """ ROS Subscriber Callback to Execute Commands via SSH """
    if msg.data in ["forward", "backward", "left", "right"]:
        send_command(msg.data)

def main():
    rospy.init_node("robot_ssh_controller", anonymous=True)
    rospy.Subscriber("/robot_movement", String, command_callback)
    rospy.spin()

if __name__ == "__main__":
    main()
