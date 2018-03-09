using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpherePosition : MonoBehaviour
{

    //public ChromaPlugin chromaPlugin;

	// Use this for initialization
	void Start ()
    {
        ChromaPlugin.InitCamera();
	}
	
	// Update is called once per frame
	void Update ()
    {
        ChromaPlugin.UpdatePlugin();
        //Debug.Log((float)ChromaPlugin.GetNormCentroid_x());
        float x = (float)ChromaPlugin.GetNormCentroid_x() - 0.5f;
        Vector3 nPos = new Vector3(x * -10.0f, 0, 0);
        transform.position = nPos;
        //Debug.Log(x);
    }

    private void OnApplicationQuit()
    {
        ChromaPlugin.TerminatePlugin();
        //TerminatePlugin();
        //Debug.Log("realeasing camera");
    }
}
