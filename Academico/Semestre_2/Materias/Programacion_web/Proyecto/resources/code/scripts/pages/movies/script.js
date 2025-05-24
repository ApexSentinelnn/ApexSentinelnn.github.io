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

// ventana flotante de imagenes para los personajes de las peliculas
const details = {
  // Personajes de "El hobbit"
  bilbo: {
    name: "Bilbo Bolsón",
    actor: "Martin Freeman",
    race: "Hobbit",
    origin: "La Comarca",
    weapon: "Dardo (Sting)",
    image:
      "https://th.bing.com/th/id/R.8edb42c54c7d4bf201551b549dab9825?rik=6jser9NMXBbHqg&riu=http%3a%2f%2fwww.elfenomeno.com%2fimag%2fusuarios%2f5%2fimagenes_hobbitactores_125.jpg&ehk=GZbv7910RbKlZF4Y1jk96yoLiqStTS1ZHmusfUsU1pg%3d&risl=&pid=ImgRaw&r=0",
    description:
      "Bilbo Bolsón es un hobbit que vive en la Comarca. Es el protagonista de 'El Hobbit', donde se embarca en una aventura inesperada con un grupo de enanos y el mago Gandalf. A lo largo de su viaje, Bilbo demuestra ser valiente y astuto, enfrentándose a dragones y trolls, y descubriendo su propio potencial.",
  },
  gandalf: {
    name: "Gandalf el Gris",
    actor: "Ian McKellen",
    race: "Maia (Istar)",
    origin: "Valinor",
    weapon: "Glamdring y Bastón",
    image:
      "https://th.bing.com/th/id/R.1de9fd651c8456e9f331519c24251a96?rik=IrS1Mgz4s4uDxA&riu=http%3a%2f%2fimages.wikia.com%2flotr%2fimages%2f8%2f8d%2fGandalf-2.jpg&ehk=Nm3tJ5SK6z6MbERxfYI6yqcd3virc6P6FuI9Uv1fxxw%3d&risl=&pid=ImgRaw&r=0",
    description:
      "Gandalf es un poderoso mago que juega un papel crucial en la historia de 'El Hobbit'. Es el mentor de Bilbo y guía a la compañía de enanos en su misión para recuperar Erebor. Su sabiduría y habilidades mágicas son fundamentales para enfrentar los peligros que encuentran en su camino.",
  },
  thorin: {
    name: "Thorin Escudo de Roble",
    actor: "Richard Armitage",
    race: "Enano",
    origin: "Erebor",
    weapon: "Hacha",
    image:
      "https://th.bing.com/th/id/R.372adfeb6b9678d4510cc8d3c217c430?rik=OTbScvAyebYrtw&riu=http%3a%2f%2fimages6.fanpop.com%2fimage%2fphotos%2f33300000%2fThorin-thorin-oakenshield-33325333-777-1024.jpg&ehk=ouyqgG7qZYbEiDM19u3iz0TeExjdiga5vVS8u1F05Uo%3d&risl=&pid=ImgRaw&r=0",
    description:
      "Thorin Escudo de Roble es el líder de la compañía de enanos que busca recuperar su hogar y tesoros del dragón Smaug. Es un guerrero valiente y noble, pero su deseo de recuperar Erebor lo lleva a la locura. A lo largo de la historia, Thorin aprende sobre la importancia de la amistad y la lealtad.",
  },
  legolas: {
    name: "Legolas",
    actor: "Orlando Bloom",
    race: "Elfo",
    origin: "Reino del Bosque",
    weapon: "Arco Élfico",
    image:
      "https://preview.redd.it/lotr-legolas-my-1st-attempt-to-create-something-out-of-a-v0-g5x5kovel3kc1.jpg?width=2397&format=pjpg&auto=webp&s=ffe01c51941adda2f82aac3f05c5b92239c429ae",
    description:
      "Legolas es un príncipe elfo del Reino del Bosque y un experto arquero. Se une a la compañía de Thorin para ayudar en la misión de recuperar Erebor. A lo largo de la historia, Legolas desarrolla una profunda amistad con Gimli, un enano, desafiando las antiguas rivalidades entre sus razas.",
  },
  smaug: {
    name: "Smaug",
    actor: "Benedict Cumberbatch",
    race: "Dragón",
    origin: "Erebor",
    weapon: "Aliento de fuego",
    image:
      "https://www.cinemascomics.com/wp-content/uploads/2022/01/smaug.jpg",
    description:
      "Smaug es un dragón temido que ocupa la Montaña Solitaria y guarda un vasto tesoro. Es astuto y manipulador, capaz de hablar y engañar a sus enemigos. Su avaricia lo lleva a atacar la ciudad de Esgaroth, lo que desencadena una serie de eventos que afectan a toda la Tierra Media.",
  },
  tauriel: {
    name: "Tauriel",
    actor: "Evangeline Lilly",
    race: "Elfo",
    origin: "Reino del Bosque",
    weapon: "Daga Élfica",
    image:
      "https://i.pinimg.com/564x/fa/1a/be/fa1abec791a075fa2d54ac8e858f8bd6.jpg",
    description:
      "Tauriel es una guerrera elfa del Reino del Bosque y capitana de la guardia. Es valiente y compasiva, y se siente atraída por Kili, un enano. A lo largo de la historia, Tauriel desafía las normas de su pueblo y lucha por proteger a los inocentes, mostrando que el amor puede superar las barreras entre razas.",
  },
  bardo: {
    name: "Bardo",
    actor: "Luke Evans",
    race: "Hombre",
    origin: "Esgaroth",
    weapon: "Ballesta",
    image:
      "https://www.elfenomeno.com/imag/usuarios/5/imagenes_hobbitactores_167.jpg",
    description:
      "Bardo es un cazador y el último descendiente de los hombres de la línea de los antiguos reyes de Esgaroth. Es valiente y decidido, dispuesto a arriesgar su vida para proteger a su pueblo. Su valentía y habilidades con la ballesta son fundamentales en la lucha contra Smaug y en la defensa de Esgaroth.",
  },
  thranduil: {
    name: "Thranduil",
    actor: "Lee Pace",
    race: "Elfo",
    origin: "Reino del Bosque",
    weapon: "Espada Élfica",
    image:
      "https://i.redd.it/thranduil-vs-elrond-v0-2b0n6y9h8qpc1.jpg?width=1280&format=pjpg&auto=webp&s=37d0e4636e4d2768738fc422e8c5f45d203e365f",
    description:
      "Thranduil es el rey de los elfos del Reino del Bosque. Es un líder sabio y poderoso, pero también arrogante y distante. A lo largo de la historia, Thranduil muestra su deseo de proteger a su pueblo y su tesoro, pero también aprende sobre la importancia de la unidad y la cooperación entre razas.",
  },
  azog: {
    name: "Azog el Profanador",
    actor: "Manu Bennett",
    race: "Orco",
    origin: "Moria",
    weapon: "Espada",
    image:
      "https://i.pinimg.com/originals/b8/15/a8/b815a875e62b732cb15d3dcd85c76722.png",
    description:
      "Azog es un orco temido y el principal antagonista de 'El Hobbit'. Es un guerrero brutal y despiadado, que busca venganza contra Thorin y su compañía. A lo largo de la historia, Azog representa la amenaza del mal y la oscuridad que acecha a la Tierra Media, desafiando a los héroes en su búsqueda.",
  },
  // Personajes de "El Señor de los Anillos"
  frodo: {
    name: "Frodo Bolsón",
    actor: "Elijah Wood",
    race: "Hobbit",
    origin: "La Comarca",
    weapon: "Dardo (Sting)",
    image:
      "https://latierramedia.com/wp-content/uploads/2022/01/frodo-edad.jpeg",
    description:
      "Frodo Bolsón es un hobbit de la Comarca que hereda el Anillo Único de su tío Bilbo. A pesar de su naturaleza pacífica, acepta la peligrosa misión de destruir el Anillo en el Monte del Destino. Su valentía y determinación, junto con la ayuda de sus amigos, lo convierten en el héroe más improbable de la Tierra Media.",
  },
  aragorn: {
    name: "Aragorn",
    actor: "Viggo Mortensen",
    race: "Hombre (Dúnadan)",
    origin: "Gondor",
    weapon: "Andúril",
    image:
      "https://images.squarespace-cdn.com/content/v1/51b3dc8ee4b051b96ceb10de/1531160000046-N7XRKI9XXWY36XU95GY9/aragorn.jpg",
    description:
      "Aragorn es el heredero legítimo del trono de Gondor, aunque vive como un Montaraz en el norte. Inicialmente reacio a aceptar su destino, se convierte en el protector de los hobbits y un líder valiente. Su amor por Arwen y su deber hacia su pueblo lo impulsan a reclamar su herencia.",
  },
  boromir: {
    name: "Boromir",
    actor: "Sean Bean",
    race: "Hombre",
    origin: "Gondor",
    weapon: "Espada y Escudo",
    image:
      "https://static.wikia.nocookie.net/lotr/images/7/78/Boromir_-_FOTR.png/revision/latest?cb=20221006035252",
    description:
      "Boromir es el hijo mayor del Senescal de Gondor, un guerrero valiente pero orgulloso. Su amor por su ciudad natal y su desesperación por protegerla lo llevan a intentar tomar el Anillo de Frodo. Sin embargo, se redime sacrificando su vida para proteger a Merry y Pippin de los Uruk-hai.",
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
