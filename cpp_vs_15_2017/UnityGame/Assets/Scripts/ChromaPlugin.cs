using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class ChromaPlugin : MonoBehaviour
{
    const string dllName = "ChromaPlugin";
    //const string dllName = "ChromaPlugin_debug";

    // ==================================================================
    // MISC API
    [DllImport(dllName, EntryPoint = "updateCount")]
    public static extern void UpdateCount();

    [DllImport(dllName, EntryPoint = "terminatePlugin")]
    public static extern void TerminatePlugin();

    // ==================================================================
    // INPUT MODULE API

    [DllImport(dllName, EntryPoint = "initCamera")]
    public static extern void InitCamera();

    [DllImport(dllName, EntryPoint = "takePhoto")]
    public static extern void TakePhoto();

    [DllImport(dllName, EntryPoint = "releaseCamera")]
    public static extern void ReleaseCamera();

    // ==================================================================
    // SEGMENTATION MODULE API
    [DllImport(dllName, EntryPoint = "calibrate")]
    public static extern void Calibrate();
    
    [DllImport(dllName, EntryPoint = "calculateMask")]
    public static extern void CalculateMask();

    [DllImport(dllName, EntryPoint = "terminateSegmentation")]
    public static extern void TerminateSegmentation();

    // ==================================================================
    // NOISE REDUCTION MODULE API
    [DllImport(dllName, EntryPoint = "reduceNoise")]
    public static extern void ReduceNoise();

    // ==================================================================
    // FEATURES MODULE API
    [DllImport(dllName, EntryPoint = "calculateCentroid")]
    public static extern void CalculateCentroid();

    [DllImport(dllName, EntryPoint = "getCentroid_x")]
    public static extern double GetCentroid_x();

    [DllImport(dllName, EntryPoint = "getCentroid_y")]
    public static extern double GetCentroid_y();

    [DllImport(dllName, EntryPoint = "getNormCentroid_x")]
    public static extern double GetNormCentroid_x();

    [DllImport(dllName, EntryPoint = "getNormCentroid_y")]
    public static extern double GetNormCentroid_y();

    public static void UpdatePlugin()
    {
        TakePhoto();
        Calibrate();
        CalculateMask();
        ReduceNoise();
        CalculateCentroid();
        //Debug.Log((float)GetNormCentroid_x());
        UpdateCount();
    }
    
    // Use this for initialization
    void Start ()
    {
        //InitCamera();
        
        //Debug.Log("initializing camera");
    }
	
	// Update is called once per frame
	void Update ()
    {
        //UpdatePlugin();
    }

    private void OnApplicationQuit()
    {
        //ReleaseCamera();
        //TerminateSegmentation();

        //TerminatePlugin();
        //Debug.Log("realeasing camera");
    }

    private void OnGUI()
    {
        //int n = (int) GetNumber();
        //bool b = IsCamera();
        //GUILayout.Label(new GUIContent(n.ToString()));
        //GUILayout.Label(new GUIContent(b.ToString()));
    }
}
