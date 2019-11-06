
using UnityEngine;
using System.Collections;

public class BlockPack : MonoBehaviour {

	public GameObject[] block;
	public int currentBlock;
	public float startPosX;
	public float startPosY;
	public int countX;
	public int countY;
	public float outX;
	public float outY;
	public string objName = "Block_";
	private int id;
	private GameObject[,] grid;
	
	void Start () 
	{
		id = 0;
		float posXreset = startPosX;
		grid = new GameObject[countX,countY];
		for(int y = 0; y < countY; y++)
		{
			startPosY -= outY;
			for(int x = 0; x < countX; x++)
			{
				id++;
				startPosX += outX;
				grid[x,y] = Instantiate(block[currentBlock], new Vector2(startPosX,startPosY), Quaternion.identity) as GameObject;
				grid[x,y].name = objName + id;
				grid[x,y].transform.parent = transform;
			}
			startPosX = posXreset;
		}
	}
}
