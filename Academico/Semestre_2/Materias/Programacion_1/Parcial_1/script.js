// Efecto de aparición suave al cargar la página
document.addEventListener('DOMContentLoaded', function() {
    const cards = document.querySelectorAll('.proyecto-card');
    cards.forEach((card, index) => {
        setTimeout(() => {
            card.style.opacity = '1';
            card.style.transform = 'translateY(0)';
        }, index * 200); // Retraso para cada tarjeta
    });
});
