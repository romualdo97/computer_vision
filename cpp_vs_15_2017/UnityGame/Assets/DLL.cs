using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class DLL : MonoBehaviour
{
    // ==================================================================
    // MISC API
    [DllImport("ChromaDLL", EntryPoint = "updateCount")]
    public static extern void UpdateCount();

    [DllImport("ChromaDLL", EntryPoint = "terminatePlugin")]
    public static extern void TerminatePlugin();

    // ==================================================================
    // INPUT MODULE API

    [DllImport("ChromaDLL", EntryPoint = "initCamera")]
    public static extern void InitCamera();

    [DllImport("ChromaDLL", EntryPoint = "takePhoto")]
    public static extern void TakePhoto();

    [DllImport("ChromaDLL", EntryPoint = "releaseCamera")]
    public static extern void ReleaseCamera();

    // ==================================================================
    // SEGMENTATION MODULE API
    [DllImport("ChromaDLL", EntryPoint = "calibrate")]
    public static extern void Calibrate();
    
    [DllImport("ChromaDLL", EntryPoint = "calculateMask")]
    public static extern void CalculateMask();

    [DllImport("ChromaDLL", EntryPoint = "terminateSegmentation")]
    public static extern void TerminateSegmentation();

    private int i = 0;
    private const int max_frames = 5;

    // Use this for initialization
    void Start ()
    {
        InitCamera();
        
        Debug.Log("initializing camera");
    }
	
	// Update is called once per frame
	void Update ()
    {
        //if (i < max_frames)
       // {
            TakePhoto();
            Calibrate();
            CalculateMask();
            UpdateCount();
            Debug.Log("taking photo");
        //}
        i++;
    }

    private void OnApplicationQuit()
    {
        //ReleaseCamera();
        //TerminateSegmentation();
        TerminatePlugin();
        Debug.Log("realeasing camera");
    }

    private void OnGUI()
    {
        //int n = (int) GetNumber();
        //bool b = IsCamera();
        //GUILayout.Label(new GUIContent(n.ToString()));
        //GUILayout.Label(new GUIContent(b.ToString()));
    }
}
