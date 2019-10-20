using UnityEngine;
using System.Collections;

public class PackCheck : MonoBehaviour {

	void Update ()
	{
		if(transform.childCount == 0) 
		{
			Menedjer.win = true;
			Destroy(gameObject);
		}
	}
}
