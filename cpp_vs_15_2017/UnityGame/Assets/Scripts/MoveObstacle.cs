using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveObstacle : MonoBehaviour
{

    public float speed = 0.2f;
    public float startZ;
    private Vector3 nPos;

	// Use this for initialization
	void Start ()
    {
        nPos = new Vector3(0, 0.5f, startZ);
	}
	
	// Update is called once per frame
	void Update ()
    {
        nPos.z += speed * -1;
        transform.position = nPos;
	}
}
