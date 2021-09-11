#include <ros/ros.h>
#include <termios.h>
#include <stdio.h>
#include <signal.h>
#include <string>
#include <std_msgs/String.h>

using namespace std;

#define KEYCODE_W       0x77
#define KEYCODE_A       0x61
#define KEYCODE_S       0x73
#define KEYCODE_D       0x64
#define KEYCODE_F       0x66
#define KEYCODE_G       0x67
#define KEYCODE_Q       0x71
#define KEYCODE_E       0x65
#define KEYCODE_STAR    0x2A
#define KEYCODE_CAP_Q   0x51

int main(int argc, char** argv)
{
    ros::init(argc, argv, "keyboard_input");
    ros::NodeHandle nh;
    
    ros::Publisher pub =  nh.advertise<std_msgs::String>("/Diablo_Teleop", 1);
    std_msgs::String cmd;

    char c;
    int kdf = 0;
    struct termios cooked, raw;

    tcgetattr(kdf, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kdf, TCSANOW, &raw);

    for(;;)
    {
        if(read(kdf, &c, 1) < 0)
        {
            printf("Error: read().\n");
            exit(-1);
        }

        switch(c)
        {
            case KEYCODE_W:
                cmd.data = "w";
                break;
            case KEYCODE_A:
                cmd.data = "a";
                break;
            case KEYCODE_S:
                cmd.data = "s";
                break;
            case KEYCODE_D:
                cmd.data = "d";
                break;
            case KEYCODE_F:
                cmd.data = "f";
                break;
            case KEYCODE_G:
                cmd.data = "g";
                break;
            case KEYCODE_Q:
                cmd.data = "q";
                break;
            case KEYCODE_E:
                cmd.data = "e";
                break;
            case KEYCODE_STAR:
                cmd.data = "*";
                break;
            case KEYCODE_CAP_Q:
                printf("Keyboard listening stop.\n");
                return 0;
            default:
                cmd.data = "";
                printf("undefined keyboard input.\n");
                break;
        }

        cout<<cmd.data;

        pub.publish(cmd);
    }

    ros::spin();
}