using Hakoniwa.PluggableAsset.Assets.Robot.Parts;
using Hakoniwa.PluggableAsset.Communication.Connector;
using Hakoniwa.PluggableAsset.Communication.Pdu;
using Hakoniwa.PluggableAsset.Assets.Robot;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace Hakoniwa.PluggableAsset.Assets.Robot.Parts.TestDriver
{
    public class Ev3ColorSensorTestDriver : MonoBehaviour, IRobotPartsSensor, IRobotPartsConfig
    {
        public Renderer my_renderer;
        private Color initial_color;
        private GameObject root;
        private PduIoConnector pdu_io;
        private IPduWriter pdu_writer;
        private string root_name;

        public int update_cycle = 10;
        public string topic_name = "ev3_sensor";
        public string roboname = "EV3TrainModel";
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
                this.my_renderer = GetComponent<Renderer>();
                this.initial_color = GetComponent<Renderer>().material.color;
                this.root = tmp;
                this.root_name = string.Copy(this.root.transform.name);
                this.pdu_io = PduIoConnector.Get(roboname);
                if (this.pdu_io == null)
                {
                    throw new ArgumentException("can not found pdu_io:" + root_name);
                }
                var pdu_writer_name = roboname + "_" + this.topic_name + "Pdu";
                this.pdu_writer = this.pdu_io.GetWriter(pdu_writer_name);
                if (this.pdu_writer == null)
                {
                    throw new ArgumentException("can not found pdu_writer:" + pdu_writer_name);
                }
            }
        }

        public bool isAttachedSpecificController()
        {
            return false;
        }
        public int sensor_id = 0;
        public Color color;
        public void UpdateSensorValues()
        {
            float rgb_r = (float)this.pdu_writer.GetReadOps().Refs("color_sensors")[this.sensor_id].GetDataUInt32("rgb_r");
            float rgb_g = (float)this.pdu_writer.GetReadOps().Refs("color_sensors")[this.sensor_id].GetDataUInt32("rgb_g");
            float rgb_b = (float)this.pdu_writer.GetReadOps().Refs("color_sensors")[this.sensor_id].GetDataUInt32("rgb_b");
            //Debug.Log("robo:" + roboname + " r=" + rgb_r + " g=" + rgb_g + " b=" + rgb_b);
            this.color = new Color(rgb_r/255f, rgb_g / 255f, rgb_b / 255f);
            //Debug.Log("MY reflect=" + this.pdu_writer.GetReadOps().Refs("color_sensors")[0].GetDataUInt32("reflect"));
        }
        public RoboPartsConfigData[] GetRoboPartsConfig()
        {
            return new RoboPartsConfigData[0];
        }
        void Update()
        {
            this.my_renderer.material.color = this.color;
        }

    }
}