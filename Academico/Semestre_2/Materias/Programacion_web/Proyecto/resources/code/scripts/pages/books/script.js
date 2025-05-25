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
  document
    .querySelectorAll(".nav-links a, .footer-links a")
    .forEach((anchor) => {
      anchor.addEventListener("click", function (e) {
        e.preventDefault();
        const targetId = this.getAttribute("href");

        // Solo hacer scroll si es un hash (#) link
        if (targetId.startsWith("#")) {
          const targetElement = document.querySelector(targetId);

          if (targetElement) {
            window.scrollTo({
              top: targetElement.offsetTop - 80,
              behavior: "smooth",
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

  // Menu
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

  // Cerrar con "Esc"
  document.addEventListener("keydown", function (e) {
    if (e.key === "Escape" && sidebar.classList.contains("active")) {
      sidebar.classList.remove("active");
      overlay.style.display = "none";
      document.body.style.overflow = "auto";
    }
  });
  // Submenús desplegables: solo uno abierto a la vez
  const sidebarTitles = document.querySelectorAll(".sidebar-title");
  sidebarTitles.forEach((title) => {
    title.addEventListener("click", function () {
      // Cerrar todos los submenús excepto el actual
      sidebarTitles.forEach((otherTitle) => {
        if (otherTitle !== this) {
          const otherSubmenu = otherTitle.nextElementSibling;
          const otherIcon = otherTitle.querySelector("i");
          if (otherSubmenu) otherSubmenu.classList.remove("active");
          if (otherIcon) otherIcon.classList.remove("active");
        }
      });
      // Alternar el submenú actual
      const submenu = this.nextElementSibling;
      const icon = this.querySelector("i");
      if (submenu) submenu.classList.toggle("active");
      if (icon) icon.classList.toggle("active");
    });
  });

  const hasSubmenus = document.querySelectorAll(".has-submenu > h3");
  hasSubmenus.forEach((item) => {
    item.addEventListener("click", function () {
      // Cerrar todos los submenús excepto el actual
      hasSubmenus.forEach((otherItem) => {
        if (otherItem !== this) {
          const otherSubmenu = otherItem.nextElementSibling;
          const otherIcon = otherItem.querySelector("i");
          if (otherSubmenu) otherSubmenu.classList.remove("active");
          if (otherIcon) otherIcon.classList.remove("active");
        }
      });
      // Alternar el submenú actual
      const submenu = this.nextElementSibling;
      const icon = this.querySelector("i");
      if (submenu) submenu.classList.toggle("active");
      if (icon) icon.classList.toggle("active");
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
  const carousel = document.querySelector(".carousel-inner");
  const items = document.querySelectorAll(".carousel-item");
  const dotsContainer = document.querySelector(".carousel-dots");
  let currentIndex = 0;

  // Crear indicadores de puntos
  items.forEach((_, index) => {
    const dot = document.createElement("span");
    dot.classList.add("dot");
    if (index === 0) dot.classList.add("active");
    dot.addEventListener("click", () => goToSlide(index));
    dotsContainer.appendChild(dot);
  });

  // Botones de navegación
  document.querySelector(".prev").addEventListener("click", () => {
    currentIndex = currentIndex > 0 ? currentIndex - 1 : items.length - 1;
    updateCarousel();
  });

  document.querySelector(".next").addEventListener("click", () => {
    currentIndex = currentIndex < items.length - 1 ? currentIndex + 1 : 0;
    updateCarousel();
  });

  // Actualizar carrusel
  function updateCarousel() {
    carousel.style.transform = `translateX(-${currentIndex * 100}%)`;
    document.querySelectorAll(".dot").forEach((dot, index) => {
      dot.classList.toggle("active", index === currentIndex);
    });
  }

  // Navegar a slide específico
  function goToSlide(index) {
    currentIndex = index;
    updateCarousel();
  }

  // Auto-avance (opcional)
  setInterval(() => {
    currentIndex = currentIndex < items.length - 1 ? currentIndex + 1 : 0;
    updateCarousel();
  }, 10000);
}

// Inicializar al cargar la página
document.addEventListener("DOMContentLoaded", initCarousel);

// ventana flotante de imagenes referente a los personajes de los libros
const details = {
  //personajes del libro "El silmarillion"
  feanor: {
    name: "Fëanor",
    race: "Elfo",
    origin: "Valinor",
    weapon: "Espada",
    image: "https://i.pinimg.com/736x/3f/7c/89/3f7c890e9d760e2aa0fd7df696cb3dd6.jpg",
    description:
      "Fëanor fue un príncipe elfo de los Noldor, conocido por su gran habilidad en la forja y su papel central en la historia de los Silmarils.",
  },
  morgoth: {
    name: "Morgoth",
    race: "Vala",
    origin: "Aman",
    weapon: "Espada",
    image: "https://preview.redd.it/what-makes-the-fallen-valar-melkor-morgoth-stand-out-v0-2uwkh63gsnqb1.jpg?auto=webp&s=73eb5b955b403211b8794453b72ce448ac6cd1cf",
    description:
      "Morgoth, originalmente conocido como Melkor, fue el primer Señor Oscuro y el principal antagonista de la historia de la Tierra Media.",
  },
  beren: {
    name: "Beren",
    race: "Hombre",
    origin: "Beleriand",
    weapon: "Espada",
    image: "https://i.gr-assets.com/images/S/compressed.photo.goodreads.com/hostedimages/1684512085i/34269641._SX540_.jpg",
    description:
      "Beren fue un hombre mortal que se enamoró de Lúthien, una elfa, y juntos emprendieron una peligrosa misión para recuperar un Silmaril.",
  },
  luthien: {
    name: "Lúthien",
    race: "Elfa",
    origin: "Beleriand",
    weapon: "Ninguno",
    image: "https://i.pinimg.com/736x/60/9e/79/609e79083157cd14b0ea131a72f31433.jpghttps://i.pinimg.com/736x/60/9e/79/609e79083157cd14b0ea131a72f31433.jpg",
    description:
      "Lúthien fue una elfa de gran belleza y poder, conocida por su amor por Beren y su valentía al enfrentarse a Morgoth.",
  },
  turin: {
    name: "Túrin Turambar",
    race: "Hombre",
    origin: "Beleriand",
    weapon: "Espada",
    image: "https://external-preview.redd.it/ISHkqa2stMoaG1JeLUqRWk3rlakJs4ZSz7enPmlOHjU.jpg?auto=webp&s=01049d3948bf978adf13a76b7af2b9ee572ff348",
    description:
      "Túrin Turambar fue un héroe trágico de la Primera Edad, conocido por su valentía y su desafortunada historia llena de maldiciones.",
  },
};

function showDetails(character) {
  const modal = document.getElementById("details-modal");
  const characterData = details[character];

  if (!characterData) {
    console.error(`No se encontraron datos para el personaje: ${character}`);
    return;
  }

  // Actualizar contenido del modal
  document.getElementById("modal-title").textContent =
    `Detalles de ${characterData.name}`;
  document.getElementById("modal-image").src = characterData.image;
  document.getElementById("character-name").textContent = characterData.name;
  document.getElementById("character-description").textContent =
    characterData.description;
  document.getElementById("character-actor").textContent = characterData.actor;
  document.getElementById("character-race").textContent = characterData.race;
  document.getElementById("character-origin").textContent =
    characterData.origin;
  document.getElementById("character-weapon").textContent =
    characterData.weapon;

  // Mostrar modal
  modal.style.display = "block";
  document.body.style.overflow = "hidden"; // Prevenir scroll del body
}

function closeDetails() {
  const modal = document.getElementById("details-modal");
  modal.style.display = "none";
  document.body.style.overflow = "auto"; // Restaurar scroll del body
}

// Cerrar modal al hacer clic fuera de él
window.onclick = function (event) {
  const modal = document.getElementById("details-modal");
  if (event.target === modal) {
    closeDetails();
  }
};

// Cerrar modal con la tecla Escape
document.addEventListener("keydown", function (event) {
  if (event.key === "Escape") {
    closeDetails();
  }
});
