using UnityEngine;

public class ObjectHighlighter : MonoBehaviour
{
    [SerializeField] private Color highlightColor = Color.yellow;
    [SerializeField] private GameObject field;
    [SerializeField] private Material flagMaterial;
    [SerializeField] private Material emptyMaterial;
    
    private Material _originalMaterial;
    private GameObject _highlightedObject;

    public LayerMask interactionLayer;

    private void Update()
    {
        HighlightObject();
        HandleSelection();
    }

    private void HighlightObject()
    {
        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, interactionLayer))
        {
            var hitObject = hit.collider.gameObject;
            
            if (hitObject == _highlightedObject) return;
            ResetHighlight();
            ApplyHighlight(hitObject);
        }
        else
        {
            ResetHighlight();
        }
    }

    private void ApplyHighlight(GameObject obj)
    {
        var renderer = obj.GetComponent<Renderer>();
        var cell = obj.GetComponent<CellBehaviour>().Cell;
        if (!renderer || cell.IsOpen) return;
        
        _originalMaterial = renderer.material;

        var highlightMaterial = new Material(renderer.material)
        {
            color = highlightColor
        };

        renderer.material = highlightMaterial;
        _highlightedObject = obj;
    }

    private void ResetHighlight()
    {
        if (!_highlightedObject) return;

        var renderer = _highlightedObject.GetComponent<Renderer>();
        if (renderer)
        {
            renderer.material = _originalMaterial;
        }
        _highlightedObject = null;
    }

    private void HandleSelection()
    {
        if (Input.GetMouseButtonDown(0) && _highlightedObject)
        {
            OpenCell(_highlightedObject);
            _highlightedObject = null;
        }

        if (Input.GetMouseButtonDown(1) && _highlightedObject)
        {
            SetFlag(_highlightedObject);
            _highlightedObject = null;
        }
    }

    private void OpenCell(GameObject obj)
    {
        field.GetComponent<FieldGenerator>().Click(obj);
    }

    private void SetFlag(GameObject obj)
    {
        obj.GetComponent<Renderer>().material = obj.GetComponent<CellBehaviour>().Cell.RightClick() ? flagMaterial : emptyMaterial;
    }
}
