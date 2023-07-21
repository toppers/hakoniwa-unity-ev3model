using Hakoniwa.PluggableAsset.Assets.Robot.Parts;
using Hakoniwa.PluggableAsset.Communication.Connector;
using Hakoniwa.PluggableAsset.Communication.Pdu;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Hakoniwa.PluggableAsset.Assets.Robot.Parts.TestDriver
{
    public class Ev3MotorControllerTestDriver : MonoBehaviour, IRobotPartsController, IRobotPartsConfig
    {
        private GameObject root;
        private string root_name;
        private PduIoConnector pdu_io;
        private IPduReader pdu_reader;

        public int update_cycle = 10;
        public string topic_name = "ev3_actuator";
        public string roboname = "EV3TrainModel";
        private int count = 0;

        public RosTopicMessageConfig[] getRosConfig()
        {
            return new RosTopicMessageConfig[0];
        }
        public void Initialize(System.Object obj)
        {
            GameObject tmp = null;
            try
            {
                tmp = obj as GameObject;
            }
            catch (InvalidCastException e)
            {
                Debug.LogError("Initialize error: " + e.Message);
                return;
            }

            if (this.root == null)
            {
                this.root = tmp;
                this.root_name = string.Copy(this.root.transform.name);
                this.pdu_io = PduIoConnector.Get(roboname);
                if (this.pdu_io == null)
                {
                    throw new ArgumentException("can not found pdu_io:" + roboname);
                }
                var pdu_io_name = roboname + "_" + this.topic_name + "Pdu";
                this.pdu_reader = this.pdu_io.GetReader(pdu_io_name);
                if (this.pdu_reader == null)
                {
                    throw new ArgumentException("can not found pdu_reader:" + pdu_io_name);
                }
            }
            this.count = 0;
        }
        public Int32 delta_vel = 1;
        private void Update()
        {
            if (Input.GetKeyDown(KeyCode.UpArrow))
            {
                this.target_velocity += delta_vel;
            }
            if (Input.GetKeyDown(KeyCode.DownArrow))
            {
                this.target_velocity -= delta_vel;
            }
            if (Input.GetKeyDown(KeyCode.Space))
            {
                Debug.Log("Space key is pressed");
                this.target_velocity = 0;
            }
        }

        public Int32 target_velocity;
        public void DoControl()
        {
            this.count++;
            if (this.count < this.update_cycle)
            {
                return;
            }
            this.count = 0;
            this.pdu_reader.GetWriteOps().Refs("motors")[0].SetData("power", this.target_velocity);
            this.pdu_reader.GetWriteOps().Refs("motors")[1].SetData("power", this.target_velocity);
        }
        public RoboPartsConfigData[] GetRoboPartsConfig()
        {
            return new RoboPartsConfigData[0];
        }
    }
}

