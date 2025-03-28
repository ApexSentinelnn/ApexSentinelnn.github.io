document.addEventListener('DOMContentLoaded', function() {
    // Animación inicial del hero
    const heroContent = document.querySelector('.hero-content');
    setTimeout(() => {
        heroContent.classList.add('animated');
    }, 300);
    
    // Animación al hacer scroll
    const animatedElements = document.querySelectorAll('.content-section, .parallax-content, .flip-card');
    const nav = document.querySelector('nav');
    
    function checkScroll() {
        // Animación de elementos
        animatedElements.forEach(element => {
            const elementTop = element.getBoundingClientRect().top;
            const windowHeight = window.innerHeight;
            
            if (elementTop < windowHeight * 0.75) {
                element.classList.add('animated');
            }
        });
        
        // Efecto en el navbar
        if (window.scrollY > 50) {
            nav.classList.add('scrolled');
        } else {
            nav.classList.remove('scrolled');
        }
    }
    
    // Smooth scroll para los enlaces del nav
    document.querySelectorAll('nav a, .footer-links a').forEach(anchor => {
        anchor.addEventListener('click', function(e) {
            e.preventDefault();
            const targetId = this.getAttribute('href');
            const targetElement = document.querySelector(targetId);
            
            window.scrollTo({
                top: targetElement.offsetTop - 80,
                behavior: 'smooth'
            });
            
            // Actualizar la URL sin recargar la página
            history.pushState(null, null, targetId);
        });
    });
    
    // Ejecutar al cargar y al hacer scroll
    checkScroll();
    window.addEventListener('scroll', checkScroll);
    
    // Efecto hover en los elementos de la galería
    const galleryItems = document.querySelectorAll('.gallery-item');
    galleryItems.forEach(item => {
        item.addEventListener('mouseenter', function() {
            this.style.transform = 'scale(1.02)';
        });
        
        item.addEventListener('mouseleave', function() {
            this.style.transform = 'scale(1)';
        });
    });
    
    // Efecto para móviles en las tarjetas
    if (window.innerWidth <= 768) {
        const flipCards = document.querySelectorAll('.flip-card');
        flipCards.forEach(card => {
            card.addEventListener('click', function() {
                this.querySelector('.flip-card-inner').classList.toggle('flipped');
            });
        });
    }
});