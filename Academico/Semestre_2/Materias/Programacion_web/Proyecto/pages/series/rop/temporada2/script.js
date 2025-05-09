document.addEventListener("DOMContentLoaded", function () {
  // Animación inicial del hero
  const heroContent = document.querySelector(".hero-content");
  setTimeout(() => {
    heroContent.classList.add("animated");
  }, 300);

  // Animación al hacer scroll
  const animatedElements = document.querySelectorAll(
    ".content-section, .flip-card",
  );
  const nav = document.querySelector("nav");

  function checkScroll() {
    // Animación de elementos
    animatedElements.forEach((element) => {
      const elementTop = element.getBoundingClientRect().top;
      const windowHeight = window.innerHeight;

      if (elementTop < windowHeight * 0.75) {
        element.classList.add("animated");
      }
    });

    // Efecto en el navbar
    if (window.scrollY > 50) {
      nav.classList.add("scrolled");
    } else {
      nav.classList.remove("scrolled");
    }
  }

// Smooth scroll para los enlaces del nav (excluyendo el logo) y footer
document.querySelectorAll(".nav-links a, .footer-links a").forEach((anchor) => {
  anchor.addEventListener("click", function (e) {
      e.preventDefault();
      const targetId = this.getAttribute("href");
      
      // Solo hacer scroll si es un hash (#) link
      if (targetId.startsWith("#")) {
          const targetElement = document.querySelector(targetId);
          
          if (targetElement) {
              window.scrollTo({
                  top: targetElement.offsetTop - 80,
                  behavior: "smooth"
              });

              // Actualizar la URL sin recargar la página
              history.pushState(null, null, targetId);
          }
      } else {
          // Si no es un hash link, permitir el comportamiento normal
          window.location.href = targetId;
      }
  });
});

  // Menú hamburguesa
  const menuToggle = document.getElementById("mobile-menu");
  const sidebar = document.getElementById("sidebar");
  const overlay = document.createElement("div");
  overlay.className = "overlay";
  document.body.appendChild(overlay);

  menuToggle.addEventListener("click", function () {
    sidebar.classList.toggle("active");
    overlay.style.display = sidebar.classList.contains("active")
      ? "block"
      : "none";
    document.body.style.overflow = sidebar.classList.contains("active")
      ? "hidden"
      : "auto";
  });

  // Cerrar menú al hacer clic en overlay
  overlay.addEventListener("click", function () {
    sidebar.classList.remove("active");
    this.style.display = "none";
    document.body.style.overflow = "auto";
  });

  // Submenús desplegables
  const sidebarTitles = document.querySelectorAll(".sidebar-title");
  sidebarTitles.forEach((title) => {
    title.addEventListener("click", function () {
      const submenu = this.nextElementSibling;
      const icon = this.querySelector("i");
      submenu.classList.toggle("active");
      icon.classList.toggle("active");
    });
  });

  const hasSubmenus = document.querySelectorAll(".has-submenu > h3");
  hasSubmenus.forEach((item) => {
    item.addEventListener("click", function () {
      const submenu = this.nextElementSibling;
      const icon = this.querySelector("i");
      submenu.classList.toggle("active");
      icon.classList.toggle("active");
    });
  });

  // Cerrar menú al hacer clic en un enlace
  const menuLinks = document.querySelectorAll(".sidebar h4");
  menuLinks.forEach((link) => {
    link.addEventListener("click", function () {
      sidebar.classList.remove("active");
      overlay.style.display = "none";
      document.body.style.overflow = "auto";
    });
  });

  // Efecto hover en los elementos de la galería
  const galleryItems = document.querySelectorAll(".gallery-item");
  galleryItems.forEach((item) => {
    item.addEventListener("mouseenter", function () {
      this.style.transform = "scale(1.02)";
    });

    item.addEventListener("mouseleave", function () {
      this.style.transform = "scale(1)";
    });
  });

  // Efecto para móviles en las tarjetas
  if (window.innerWidth <= 768) {
    const flipCards = document.querySelectorAll(".flip-card");
    flipCards.forEach((card) => {
      card.addEventListener("click", function () {
        this.querySelector(".flip-card-inner").classList.toggle("flipped");
      });
    });
  }

  // Ejecutar al cargar y al hacer scroll
  checkScroll();
  window.addEventListener("scroll", checkScroll);
});

//Carrusel
// Carrusel de imágenes
function initCarousel() {
  const carousel = document.querySelector('.carousel-inner');
  const items = document.querySelectorAll('.carousel-item');
  const dotsContainer = document.querySelector('.carousel-dots');
  let currentIndex = 0;

  // Crear indicadores de puntos
  items.forEach((_, index) => {
      const dot = document.createElement('span');
      dot.classList.add('dot');
      if (index === 0) dot.classList.add('active');
      dot.addEventListener('click', () => goToSlide(index));
      dotsContainer.appendChild(dot);
  });

  // Botones de navegación
  document.querySelector('.prev').addEventListener('click', () => {
      currentIndex = (currentIndex > 0) ? currentIndex - 1 : items.length - 1;
      updateCarousel();
  });

  document.querySelector('.next').addEventListener('click', () => {
      currentIndex = (currentIndex < items.length - 1) ? currentIndex + 1 : 0;
      updateCarousel();
  });

  // Actualizar carrusel
  function updateCarousel() {
      carousel.style.transform = `translateX(-${currentIndex * 100}%)`;
      document.querySelectorAll('.dot').forEach((dot, index) => {
          dot.classList.toggle('active', index === currentIndex);
      });
  }

  // Navegar a slide específico
  function goToSlide(index) {
      currentIndex = index;
      updateCarousel();
  }

  // Auto-avance (opcional)
  setInterval(() => {
      currentIndex = (currentIndex < items.length - 1) ? currentIndex + 1 : 0;
      updateCarousel();
  }, 10000);
}

// Inicializar al cargar la página
document.addEventListener('DOMContentLoaded', initCarousel);


// ventana flotante de imagenes
const details = {
  bilbo: {
      image: "https://th.bing.com/th/id/R.8edb42c54c7d4bf201551b549dab9825?rik=6jser9NMXBbHqg&riu=http%3a%2f%2fwww.elfenomeno.com%2fimag%2fusuarios%2f5%2fimagenes_hobbitactores_125.jpg&ehk=GZbv7910RbKlZF4Y1jk96yoLiqStTS1ZHmusfUsU1pg%3d&risl=&pid=ImgRaw&r=0",
  }, 
  gandalf: {
      image: "https://th.bing.com/th/id/R.1de9fd651c8456e9f331519c24251a96?rik=IrS1Mgz4s4uDxA&riu=http%3a%2f%2fimages.wikia.com%2flotr%2fimages%2f8%2f8d%2fGandalf-2.jpg&ehk=Nm3tJ5SK6z6MbERxfYI6yqcd3virc6P6FuI9Uv1fxxw%3d&risl=&pid=ImgRaw&r=0",
  },
  thorin: {
      image: "https://th.bing.com/th/id/R.372adfeb6b9678d4510cc8d3c217c430?rik=OTbScvAyebYrtw&riu=http%3a%2f%2fimages6.fanpop.com%2fimage%2fphotos%2f33300000%2fThorin-thorin-oakenshield-33325333-777-1024.jpg&ehk=ouyqgG7qZYbEiDM19u3iz0TeExjdiga5vVS8u1F05Uo%3d&risl=&pid=ImgRaw&r=0",
  }
};

function showDetails(character) {
  const modal = document.getElementById('details-modal');
  const image = document.getElementById('modal-image');
  const quote = document.getElementById('modal-quote');

  image.src = details[character].image;
  quote.textContent = details[character].quote;

  modal.style.display = 'block';
}

function closeDetails() {
  const modal = document.getElementById('details-modal');
  modal.style.display = 'none';
}