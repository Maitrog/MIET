using UnityEngine;

public class Character : MonoBehaviour
{
    private CharacterController _controller;
    [SerializeField] private Camera playerCamera;
    [SerializeField] private float speed = 5.0f;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        _controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {
        // var move = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        
        var move = GetMoveDirection(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));
        _controller.Move(move * (speed * Time.deltaTime));
    }

    private Vector3 GetMoveDirection(float horizontal, float vertical)
    {
        var forward = playerCamera.transform.forward; 
        var right = playerCamera.transform.right;

        forward.y = 0;
        right.y = 0;
        
        forward.Normalize();
        right.Normalize();

        var direction = (forward * vertical + right * horizontal).normalized;

        return direction;
    }
}
