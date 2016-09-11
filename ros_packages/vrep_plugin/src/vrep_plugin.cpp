// This file is part of the ROS PLUGIN for V-REP
// 
// Copyright 2006-2016 Coppelia Robotics GmbH. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// A big thanks to Svetlin Penkov for his precious help!
// 
// The ROS PLUGIN is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The ROS PLUGIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// THE ROS PLUGIN IS DISTRIBUTED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY. THE USER WILL USE IT AT HIS/HER OWN RISK. THE ORIGINAL
// AUTHORS AND COPPELIA ROBOTICS GMBH WILL NOT BE LIABLE FOR DATA LOSS,
// DAMAGES, LOSS OF PROFITS OR ANY OTHER KIND OF LOSS WHILE USING OR
// MISUSING THIS SOFTWARE.
// 
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the ROS PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.3.2 on August 29th 2016

#include "../include/v_repLib.h"
#include "../include/scriptFunctionData.h"
#include <boost/lexical_cast.hpp>
#include "../include/vrep_plugin/vrep_plugin.h"
#include "../include/vrep_plugin/ROS_server.h"

#include "ros/ros.h"
#include "std_msgs/Float32.h"

#include <iostream>
#include <opencv2/opencv.hpp>

#define PLUGIN_VERSION 5 // 5 since 3.3.1 (using stacks to exchange data with scripts)

#define CONCAT(x,y,z) x y z
#define strConCat(x,y,z)    CONCAT(x,y,z)

LIBRARY vrepLib; // the V-REP library that we will dynamically load and bind

// --------------------------------------------------------------------------------------
// simExtROS_enablePublisher
// --------------------------------------------------------------------------------------
#define LUA_ENABLEPUBLISHER_COMMAND "simExtROS_enablePublisher"

const int inArgs_ENABLEPUBLISHER[]={
    7,
    sim_script_arg_string,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
    sim_script_arg_string,0,
    sim_script_arg_int32,0,
};

void LUA_ENABLEPUBLISHER_CALLBACK(SScriptCallBack* p)
{

    CScriptFunctionData D;
    std::string effectiveTopicName;
    if (D.readDataFromStack(p->stackID,inArgs_ENABLEPUBLISHER,inArgs_ENABLEPUBLISHER[0]-1,LUA_ENABLEPUBLISHER_COMMAND)) // -1 because the last argument is optional
    {
        std::vector<CScriptFunctionDataItem>* inData=D.getInDataPtr();
        std::string topicName(inData->at(0).stringData[0]);
        if (topicName.length()>0)
        {
            int queueSize=inData->at(1).int32Data[0];
            int streamCmd=inData->at(2).int32Data[0];
            int auxInt1=inData->at(3).int32Data[0];
            int auxInt2=inData->at(4).int32Data[0];
            std::string auxString(inData->at(5).stringData[0]);
            int publishCnt=0; // 0 is the default value for this optional argument
            if (inData->size()>6)
                publishCnt=inData->at(6).int32Data[0];
            
            int errorModeSaved;
            simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
            simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

            effectiveTopicName=ROS_server::addPublisher(topicName.c_str(),queueSize,streamCmd,auxInt1,auxInt2,auxString.c_str(),publishCnt);

            simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings

            if (effectiveTopicName.length()==0)
                simSetLastError(LUA_ENABLEPUBLISHER_COMMAND, "Topic could not be published."); // output an error
        }
        else
            simSetLastError(LUA_ENABLEPUBLISHER_COMMAND, "Invalid topic name."); // output an error
    }
    if (effectiveTopicName.size()!=0)
        D.pushOutData(CScriptFunctionDataItem(effectiveTopicName));
    D.writeDataToStack(p->stackID);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// simExtROS_disablePublisher
// --------------------------------------------------------------------------------------
#define LUA_DISABLEPUBLISHER_COMMAND "simExtROS_disablePublisher"

const int inArgs_DISABLEPUBLISHER[]={
    1,
    sim_script_arg_string,0,
};

void LUA_DISABLEPUBLISHER_CALLBACK(SScriptCallBack* p)
{

    CScriptFunctionData D;
    int result=-1;
    if (D.readDataFromStack(p->stackID,inArgs_DISABLEPUBLISHER,inArgs_DISABLEPUBLISHER[0],LUA_DISABLEPUBLISHER_COMMAND))
    {
        std::vector<CScriptFunctionDataItem>* inData=D.getInDataPtr();
        std::string topicName(inData->at(0).stringData[0]);
        if (topicName.length()>0)
        {
            int errorModeSaved;
            simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
            simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

            result=ROS_server::removePublisher(topicName.c_str(),false);

            simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings

            if (result==-1)
                simSetLastError(LUA_DISABLEPUBLISHER_COMMAND, "Topic could not be unpublished."); // output an error
        }
        else
            simSetLastError(LUA_DISABLEPUBLISHER_COMMAND, "Invalid topic name."); // output an error
    }
    D.pushOutData(CScriptFunctionDataItem(result));
    D.writeDataToStack(p->stackID);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// simExtROS_wakePublisher
// --------------------------------------------------------------------------------------
#define LUA_WAKEPUBLISHER_COMMAND "simExtROS_wakePublisher"

const int inArgs_WAKEPUBLISHER[]={
    2,
    sim_script_arg_string,0,
    sim_script_arg_int32,0,
};

void LUA_WAKEPUBLISHER_CALLBACK(SScriptCallBack* p)
{

    CScriptFunctionData D;
    int result=-1;
    if (D.readDataFromStack(p->stackID,inArgs_WAKEPUBLISHER,inArgs_WAKEPUBLISHER[0],LUA_WAKEPUBLISHER_COMMAND))
    {
        std::vector<CScriptFunctionDataItem>* inData=D.getInDataPtr();
        std::string topicName(inData->at(0).stringData[0]);
        if (topicName.length()>0)
        {
            int publishCnt=inData->at(1).int32Data[0];

            int errorModeSaved;
            simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
            simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

            result=ROS_server::wakePublisher(topicName.c_str(),publishCnt);

            simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings

            if (result==-2)
                simSetLastError(LUA_WAKEPUBLISHER_COMMAND, "Topic could not be found."); // output an error
        }
        else
            simSetLastError(LUA_WAKEPUBLISHER_COMMAND, "Invalid topic name."); // output an error
    }
    D.pushOutData(CScriptFunctionDataItem(result));
    D.writeDataToStack(p->stackID);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// simExtROS_enableSubscriber
// --------------------------------------------------------------------------------------
#define LUA_ENABLESUBSCRIBER_COMMAND "simExtROS_enableSubscriber"

const int inArgs_ENABLESUBSCRIBER[]={
    8,
    sim_script_arg_string,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
    sim_script_arg_string,0,
    sim_script_arg_int32,0,
    sim_script_arg_int32,0,
};

void LUA_ENABLESUBSCRIBER_CALLBACK(SScriptCallBack* p)
{

    CScriptFunctionData D;
    int result=-1;
    if (D.readDataFromStack(p->stackID,inArgs_ENABLESUBSCRIBER,inArgs_ENABLESUBSCRIBER[0]-2,LUA_ENABLESUBSCRIBER_COMMAND)) // -2 because the last two args are optional
    {
        std::vector<CScriptFunctionDataItem>* inData=D.getInDataPtr();
        std::string topicName(inData->at(0).stringData[0]);
        if (topicName.length()>0)
        {
            int queueSize=inData->at(1).int32Data[0];
            int streamCmd=inData->at(2).int32Data[0];
            int auxInt1=inData->at(3).int32Data[0];
            int auxInt2=inData->at(4).int32Data[0];
            std::string auxString(inData->at(5).stringData[0]);
            int callbackTag_before=-1; // no callback (default)
            int callbackTag_after=-1; // no callback (default)
            if (inData->size()>6)
                callbackTag_before=inData->at(6).int32Data[0];
            if (inData->size()>7)
                callbackTag_after=inData->at(7).int32Data[0];
            
            int errorModeSaved;
            simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
            simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

            result=ROS_server::addSubscriber(topicName.c_str(),queueSize,streamCmd,auxInt1,auxInt2,auxString.c_str(),callbackTag_before,callbackTag_after);

            simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings

            if (result==-1)
                simSetLastError(LUA_ENABLESUBSCRIBER_COMMAND, "Topic could not be subscribed."); // output an error
        }
        else
            simSetLastError(LUA_ENABLESUBSCRIBER_COMMAND, "Invalid topic name."); // output an error
    }
    D.pushOutData(CScriptFunctionDataItem(result));
    D.writeDataToStack(p->stackID);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// simExtROS_disableSubscriber
// --------------------------------------------------------------------------------------
#define LUA_DISABLESUBSCRIBER_COMMAND "simExtROS_disableSubscriber"

const int inArgs_DISABLESUBSCRIBER[]={
    1,
    sim_script_arg_int32,0,
};

void LUA_DISABLESUBSCRIBER_CALLBACK(SScriptCallBack* p)
{

    CScriptFunctionData D;
    bool result=false;
    if (D.readDataFromStack(p->stackID,inArgs_DISABLESUBSCRIBER,inArgs_DISABLESUBSCRIBER[0],LUA_DISABLESUBSCRIBER_COMMAND))
    {
        std::vector<CScriptFunctionDataItem>* inData=D.getInDataPtr();
        int errorModeSaved;
        simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
        simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

        result=ROS_server::removeSubscriber(inData->at(0).int32Data[0]);

        simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings

        if (!result)
            simSetLastError(LUA_DISABLESUBSCRIBER_COMMAND, "Topic could not be unsubscribed."); // output an error
    }
    D.pushOutData(CScriptFunctionDataItem(result));
    D.writeDataToStack(p->stackID);
}
// --------------------------------------------------------------------------------------


// This is the plugin start routine (called just once, just after the plugin was loaded):
VREP_DLLEXPORT unsigned char v_repStart(void* reservedPointer,int reservedInt)
{
    // Dynamically load and bind V-REP functions:
    // ******************************************
    // 1. Figure out this plugin's directory:
    char curDirAndFile[1024];
    getcwd(curDirAndFile, sizeof(curDirAndFile));

    std::string currentDirAndPath(curDirAndFile);
    // 2. Append the V-REP library's name:
    std::string temp(currentDirAndPath);
    #ifdef _WIN32
        temp+="\\v_rep.dll";
    #elif defined (__linux)
        temp+="/libv_rep.so";
    #elif defined (__APPLE__)
        temp+="/libv_rep.dylib";
    #endif

    // 3. Load the V-REP library:
    vrepLib=loadVrepLibrary(temp.c_str());
    if (vrepLib==NULL)
    {
        std::cout << "Error, could not find or correctly load the V-REP library. Cannot start 'ROS' plugin.\n";
        return(0); // Means error, V-REP will unload this plugin
    }
    if (getVrepProcAddresses(vrepLib)==0)
    {
        std::cout << "Error, could not find all required functions in the V-REP library. Cannot start 'ROS' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************

    // Check the version of V-REP:
    // ******************************************
    int vrepVer;
    simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
    if (vrepVer<20605) // if V-REP version is smaller than 2.06.04
    {
        std::cout << "Sorry, your V-REP copy is somewhat old. Cannot start 'ROS' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************
    

    
    // Initialize the ROS part:
    if(!ROS_server::initialize()) 
    {
        std::cout << "ROS master is not running. Cannot start 'ROS' plugin.\n";
        return (0); //If the master is not running then the plugin is not loaded.
    }
    
    // Register the new Lua commands:
    simRegisterScriptCallbackFunction(strConCat(LUA_ENABLEPUBLISHER_COMMAND,"@","Ros"),strConCat("string topicName=",LUA_ENABLEPUBLISHER_COMMAND,"(string topicName,number queueSize,number rosStreamCmd,number auxInt1,number auxInt2,string auxString,number publishCnt=0)"),LUA_ENABLEPUBLISHER_CALLBACK);
    simRegisterScriptCallbackFunction(strConCat(LUA_DISABLEPUBLISHER_COMMAND,"@","Ros"),strConCat("number referenceCounter=",LUA_DISABLEPUBLISHER_COMMAND,"(string topicName)"),LUA_DISABLEPUBLISHER_CALLBACK);
    simRegisterScriptCallbackFunction(strConCat(LUA_WAKEPUBLISHER_COMMAND,"@","Ros"),strConCat("number result=",LUA_WAKEPUBLISHER_COMMAND,"(string topicName,number publishCnt)"),LUA_WAKEPUBLISHER_CALLBACK);
    simRegisterScriptCallbackFunction(strConCat(LUA_ENABLESUBSCRIBER_COMMAND,"@","Ros"),strConCat("number subscriberId=",LUA_ENABLESUBSCRIBER_COMMAND,"(string topicName,number queueSize,number rosStreamCmd,number auxInt1,number auxInt2,string auxString,number callbackTag_before=-1,number callbackTag_after=-1)"),LUA_ENABLESUBSCRIBER_CALLBACK);
    simRegisterScriptCallbackFunction(strConCat(LUA_DISABLESUBSCRIBER_COMMAND,"@","Ros"),strConCat("boolean result=",LUA_DISABLESUBSCRIBER_COMMAND,"(number subscriberID)"),LUA_DISABLESUBSCRIBER_CALLBACK);


    // Publisher constants:
    simRegisterScriptVariable("simros_strmcmd_get_laser_scanner_data",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_laser_scanner_data))).c_str(),0);    
    simRegisterScriptVariable("simros_strmcmd_get_odom_data",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_odom_data))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_object_selection",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_selection))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_array_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_array_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_boolean_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_boolean_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_dialog_result",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_dialog_result))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_floating_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_floating_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_integer_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_integer_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_joint_state",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_joint_state))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_object_pose",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_pose))).c_str(),0);
//  simRegisterScriptVariable("simros_strmcmd_get_object_quaternion",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_quaternion))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_object_parent",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_parent))).c_str(),0);
//  simRegisterScriptVariable("simros_strmcmd_get_object_position",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_position))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_objects",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_objects))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_string_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_string_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_ui_event_button",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_ui_event_button))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_vision_sensor_depth_buffer",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_vision_sensor_depth_buffer))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_vision_sensor_image",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_vision_sensor_image))).c_str(),0);
//  simRegisterScriptVariable("simros_strmcmd_get_joint_force",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_joint_force))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_read_collision",(boost::lexical_cast<std::string>(int(simros_strmcmd_read_collision))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_read_distance",(boost::lexical_cast<std::string>(int(simros_strmcmd_read_distance))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_read_force_sensor",(boost::lexical_cast<std::string>(int(simros_strmcmd_read_force_sensor))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_read_proximity_sensor",(boost::lexical_cast<std::string>(int(simros_strmcmd_read_proximity_sensor))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_read_vision_sensor",(boost::lexical_cast<std::string>(int(simros_strmcmd_read_vision_sensor))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_object_float_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_float_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_object_int_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_int_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_ui_button_property",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_ui_button_property))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_ui_slider",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_ui_slider))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_float_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_float_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_integer_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_integer_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_string_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_string_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_and_clear_string_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_and_clear_string_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_transform",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_transform))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_range_finder_data",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_range_finder_data))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_depth_sensor_data",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_depth_sensor_data))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_vision_sensor_info",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_vision_sensor_info))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_twist_status",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_twist_status))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_get_object_group_data",(boost::lexical_cast<std::string>(int(simros_strmcmd_get_object_group_data))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_receive_data_from_script_function",(boost::lexical_cast<std::string>(int(simros_strmcmd_receive_data_from_script_function))).c_str(),0);

    // Subscriber constants:
    simRegisterScriptVariable("simros_strmcmd_add_status_bar_message",(boost::lexical_cast<std::string>(int(simros_strmcmd_add_status_bar_message))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_object_selection",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_selection))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_auxiliary_console_print",(boost::lexical_cast<std::string>(int(simros_strmcmd_auxiliary_console_print))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_array_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_array_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_boolean_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_boolean_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_floating_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_floating_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_integer_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_integer_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_joint_force",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joint_force))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_joint_position",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joint_position))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_joint_target_position",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joint_target_position))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_joint_target_velocity",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joint_target_velocity))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_vision_sensor_image",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_vision_sensor_image))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_object_float_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_float_parameter))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_object_int_parameter",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_int_parameter))).c_str(),0);
//  simRegisterScriptVariable("simros_strmcmd_set_object_orientation",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_orientation))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_object_position",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_position))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_object_pose",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_pose))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_joint_state",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joint_state))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_object_quaternion",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_object_quaternion))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_ui_button_label",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_ui_button_label))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_ui_button_property",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_ui_button_property))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_ui_slider",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_ui_slider))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_clear_float_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_clear_float_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_clear_integer_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_clear_integer_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_clear_string_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_clear_string_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_float_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_float_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_integer_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_integer_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_string_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_string_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_append_string_signal",(boost::lexical_cast<std::string>(int(simros_strmcmd_append_string_signal))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_twist_command",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_twist_command))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_set_joy_sensor",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joy_sensor))).c_str(),0);
//  simRegisterScriptVariable("simros_strmcmd_set_joint_trajectory",(boost::lexical_cast<std::string>(int(simros_strmcmd_set_joint_trajectory))).c_str(),0);
    simRegisterScriptVariable("simros_strmcmd_send_data_to_script_function",(boost::lexical_cast<std::string>(int(simros_strmcmd_send_data_to_script_function))).c_str(),0);

    return(PLUGIN_VERSION); // initialization went fine, we return the version number of this plugin (can be queried with simGetModuleName)
}

// This is the plugin end routine (called just once, when V-REP is ending, i.e. releasing this plugin):
VREP_DLLEXPORT void v_repEnd()
{
    ROS_server::shutDown(); // shutdown the ROS_server
    unloadVrepLibrary(vrepLib); // release the library
}

// This is the plugin messaging routine (i.e. V-REP calls this function very often, with various messages):
VREP_DLLEXPORT void* v_repMessage(int message,int* auxiliaryData,void* customData,int* replyData)
{ 
    // This is called quite often. Just watch out for messages/events you want to handle
    // Keep following 4 lines at the beginning and unchanged:
    int errorModeSaved;
    simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
    simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);
    void* retVal=NULL;

    // Here we can intercept many messages from V-REP (actually callbacks). Only the most important messages are listed here:

    if (message==sim_message_eventcallback_instancepass)
    { 
        // This message is sent each time the scene was rendered (well, shortly after) (very often)
        // When a simulation is not running, but you still need to execute some commands, then put some code here
        ROS_server::instancePass();
    }

    if (message==sim_message_eventcallback_mainscriptabouttobecalled)
    { 
        // Main script is about to be run (only called while a simulation is running (and not paused!))
        //
        // This is a good location to execute simulation commands
        
        if (ROS_server::mainScriptAboutToBeCalled())
        {
            simSetBooleanParameter(sim_boolparam_waiting_for_trigger,1); // the remote API client can query that value
            replyData[0]=0; // this tells V-REP that we don't wanna execute the main script
        }
        else
            simSetBooleanParameter(sim_boolparam_waiting_for_trigger,0); // the remote API client can query that value
    }

    if (message==sim_message_eventcallback_simulationabouttostart)
    { 
        // Simulation is about to start
        
        ROS_server::simulationAboutToStart();
    }

    if (message==sim_message_eventcallback_simulationended)
    { 
        // Simulation just ended
        simSetBooleanParameter(sim_boolparam_waiting_for_trigger,0); // the remote API client can query that value
        ROS_server::simulationEnded();
    }

    // Keep following unchanged:
    simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings
    return(retVal);
}

