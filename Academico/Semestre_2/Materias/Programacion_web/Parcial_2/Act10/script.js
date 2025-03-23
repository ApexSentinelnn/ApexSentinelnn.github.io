// Función para resaltar áreas
function highlightArea(event, area) {
    let highlight = document.getElementById('highlight');
    let img = document.getElementById('mainImage');

    let boundingBox = img.getBoundingClientRect();
    let offsetX = boundingBox.left;
    let offsetY = boundingBox.top;

    let coords = event.target.coords.split(",").map(Number);
    let xMin = Math.min(...coords.filter((_, i) => i % 2 === 0));
    let yMin = Math.min(...coords.filter((_, i) => i % 2 !== 0));
    let xMax = Math.max(...coords.filter((_, i) => i % 2 === 0));
    let yMax = Math.max(...coords.filter((_, i) => i % 2 !== 0));

    highlight.style.left = `${xMin + offsetX}px`;
    highlight.style.top = `${yMin + offsetY}px`;
    highlight.style.width = `${xMax - xMin}px`;
    highlight.style.height = `${yMax - yMin}px`;
    highlight.style.opacity = 1;
}

// Función para ocultar resaltado
function removeHighlight() {
    document.getElementById('highlight').style.opacity = 0;
}
