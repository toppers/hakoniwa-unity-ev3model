using Hakoniwa.PluggableAsset.Assets.Robot.Parts;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Hakoniwa.PluggableAsset.Assets.Robot.EV3
{
    public class GearController : MonoBehaviour, IRobotPartsSensor
    {
        public GameObject mover;
        public float rotation_angle_per_sec = 1f;
        private float rotation_angle_per_fixupdate = 1f;
        private bool isMovingMode = false;
        private float targetAngle = 90;
        private float currentAngle = 0;
        private GearSensor[] sensors;

        public void Initialize(object root)
        {
            this.isMovingMode = false;
            this.rotation_angle_per_fixupdate = rotation_angle_per_sec / Time.fixedDeltaTime;
            this.sensors = this.GetComponentsInChildren<GearSensor>();
            foreach (var entry in sensors)
            {
                entry.isTouched = false;
            }
            //Debug.Log("Initialize Gear Control: sensor num=" + this.sensors.Length);
        }

        // Update is called once per frame
        public void UpdateSensorValues()
        {
            if (this.isMovingMode)
            {
                //Debug.Log("obj=" + this.name);
                //Debug.Log("angle=" + this.currentAngle);
                this.mover.transform.Rotate(new Vector3(0, rotation_angle_per_fixupdate, 0));
                this.currentAngle += rotation_angle_per_fixupdate;
                if (this.currentAngle >= this.targetAngle)
                {
                    this.currentAngle = 0;
                    this.isMovingMode = false;
                }
            }
            else
            {
                foreach (var e in this.sensors)
                {
                    if (e.IsTouched())
                    {
                        this.isMovingMode = true;
                        break;
                    }
                }
            }

        }

        public bool isAttachedSpecificController()
        {
            return false;
        }


        public RosTopicMessageConfig[] getRosConfig()
        {
            return null;
        }
    }

}
