// NULLcode Studio © 2015
// null-code.ru

using UnityEngine;
using System.Collections;

public class Ball : MonoBehaviour {

	public int speed;
	public AudioClip[] hit;
	private Rigidbody2D body;
	private int hitTimeOut;
	private float hitTimeOutPositionX;
	private float hitTimeOutPositionY;

	public bool isAlive;

	void Start () 
	{
		body = GetComponent<Rigidbody2D>();
		hitTimeOut = 0;
		hitTimeOutPositionX = 0;
		hitTimeOutPositionY = 0;
		isAlive = true;
	}

	void FixedUpdate () 
	{
		// Ограничение скорости по осям Х и Y
		if(Mathf.Abs(body.velocity.x) > speed/100f)
		{
			body.velocity = new Vector2(Mathf.Sign(body.velocity.x) * speed/100f, body.velocity.y);
		}
		if(Mathf.Abs(body.velocity.y) > speed/100f)
		{
			body.velocity = new Vector2(body.velocity.x, Mathf.Sign(body.velocity.y) * speed/100f);
		}
	}

	void OnCollisionEnter2D(Collision2D coll)
	{
		// Если шарик "залипнет" на оси Х, то будет добавлена сила, чтобы изменить траекторию
		if(hitTimeOutPositionX != transform.position.x)
		{
			hitTimeOutPositionX = transform.position.x;
		}
		else
		{
			hitTimeOut++;
			if(hitTimeOut == 2)
			{
				hitTimeOut = 0;
				if(hitTimeOutPositionX < 0)
				{
					body.AddForce(new Vector2(speed, Random.Range(-speed, speed)));
				}
				else
				{
					body.AddForce(new Vector2(-speed, Random.Range(-speed, speed)));
				}
			}
		}
		// Тоже самое для Y
		if(hitTimeOutPositionY != transform.position.y)
		{
			hitTimeOutPositionY = transform.position.y;
		}
		else
		{
			hitTimeOut++;
			if(hitTimeOut == 2)
			{
				hitTimeOut = 0;
				if(hitTimeOutPositionY < 0)
				{
					body.AddForce(new Vector2(Random.Range(-speed, speed), speed));
				}
				else
				{
					body.AddForce(new Vector2(Random.Range(-speed, speed), -speed));
				}
			}
		}

		if(coll.transform.CompareTag("Block"))
		{
			Block b = coll.transform.GetComponent<Block>();
			switch(b.ID)
			{
			case 0: // Если ID блока = 0
				AudioSource.PlayClipAtPoint(hit[0], transform.position);
				break;
			case 1:
				// и т.д.
				break;
			}
			b.HP -= 1;
			if(b.HP <= 0)
			{
				Menedjer.score++;
				Destroy(coll.transform.gameObject);
			}
		}
	}

	void OnTriggerEnter2D(Collider2D coll)
	{
		if(coll.transform.CompareTag("Killbox"))
		{
			if(!Menedjer.win && !Menedjer.lose)
			{
				if (Menedjer.playerLife > 0) 
				{
					Menedjer.playerLife--;
					isAlive = false;
				} 
				else 
				{
					Menedjer.lose = true;
				}
			}
			Destroy(gameObject);
		}
	}
}
