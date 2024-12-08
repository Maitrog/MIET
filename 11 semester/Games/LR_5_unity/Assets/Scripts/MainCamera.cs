using System;
using UnityEngine;

public class MainCamera : MonoBehaviour
{
    [SerializeField] private Transform target;
    [SerializeField] private float mouseSensitivity = 2f;
    private float _yRotation = 0f;

    private Vector3 _offset;

    private void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    private void Awake()
    {
        _offset = transform.position - target.position;
    }

    private void LateUpdate()
    {
        var mouseX = Input.GetAxis("Mouse X") * mouseSensitivity;
        var mouseY = Input.GetAxis("Mouse Y") * mouseSensitivity;
        
        _yRotation -= mouseY;
        _yRotation = Mathf.Clamp(_yRotation, -90f, 90f);
        transform.localEulerAngles = Vector3.right * _yRotation;
        
        target.Rotate(Vector3.up * mouseX);
        
        transform.position = target.position + _offset;
        // transform.position = player.position + _offset;
    }
}
