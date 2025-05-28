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
    actor: "Fëanor",
    race: "Elfo",
    origin: "Valinor",
    weapon: "Espada",
    image: "https://i.pinimg.com/736x/3f/7c/89/3f7c890e9d760e2aa0fd7df696cb3dd6.jpg",
    description:
      "Fëanor fue un príncipe elfo de los Noldor, conocido por su gran habilidad en la forja y su papel central en la historia de los Silmarils.",
  },
  morgoth: {
    name: "Morgoth",
    actor: "Morgoth",
    race: "Vala",
    origin: "Aman",
    weapon: "Espada",
    image: "https://preview.redd.it/what-makes-the-fallen-valar-melkor-morgoth-stand-out-v0-2uwkh63gsnqb1.jpg?auto=webp&s=73eb5b955b403211b8794453b72ce448ac6cd1cf",
    description:
      "Morgoth, originalmente conocido como Melkor, fue el primer Señor Oscuro y el principal antagonista de la historia de la Tierra Media.",
  },
  beren: {
    name: "Beren",
    actor: "Beren",
    race: "Hombre",
    origin: "Beleriand",
    weapon: "Espada",
    image: "https://i.gr-assets.com/images/S/compressed.photo.goodreads.com/hostedimages/1684512085i/34269641._SX540_.jpg",
    description:
      "Beren fue un hombre mortal que se enamoró de Lúthien, una elfa, y juntos emprendieron una peligrosa misión para recuperar un Silmaril.",
  },
  luthien: {
    name: "Lúthien",
    actor: "Lúthien",
    race: "Elfa",
    origin: "Beleriand",
    weapon: "Ninguno",
    image: "https://i.pinimg.com/736x/60/9e/79/609e79083157cd14b0ea131a72f31433.jpg",
    description:
      "Lúthien fue una elfa de gran belleza y poder, conocida por su amor por Beren y su valentía al enfrentarse a Morgoth.",
  },
  turin: {
    name: "Túrin Turambar",
    actor: "Túrin",
    race: "Hombre",
    origin: "Beleriand",
    weapon: "Espada",
    image: "https://external-preview.redd.it/ISHkqa2stMoaG1JeLUqRWk3rlakJs4ZSz7enPmlOHjU.jpg?auto=webp&s=01049d3948bf978adf13a76b7af2b9ee572ff348",
    description:
      "Túrin Turambar fue un héroe trágico de la Primera Edad, conocido por su valentía y su desafortunada historia llena de maldiciones.",
  },
  //personajes del libro "El hobbit"
  bilbo: {
    name: "Bilbo Bolsón",
    actor: "Bilbo",
    race: "Hobbit",
    origin: "La Comarca",
    weapon: "Daga",
    image: "https://i.pinimg.com/736x/c7/c9/29/c7c9294b80cecd61df6c010971d1cf52.jpg",
    description:
      "Bilbo Bolsón es un hobbit que se embarca en una aventura inesperada con un grupo de enanos y el mago Gandalf.",
  },
  gandalf: {
    name: "Gandalf",
    actor: "Gandalf",
    race: "Maya",
    origin: "Aman",
    weapon: "Bastón",
    image: "https://upload.wikimedia.org/wikipedia/commons/e/ea/GANDALF.jpg",
    description:
      "Gandalf es un mago sabio y poderoso que guía a Bilbo y los enanos en su búsqueda para recuperar el Reino de Erebor.",
  },
  thorin: {
    name: "Thorin Escudo de Roble",
    actor: "Thorin",
    race: "Enano",
    origin: "Erebor",
    weapon: "Hacha",
    image: "https://tolkiendili.com/w/images/thumb/0/0f/Jenny_Dolfen_-_Thorin.jpg/250px-Jenny_Dolfen_-_Thorin.jpg",
    description:
      "Thorin es el líder de la compañía de enanos que busca recuperar su hogar y tesoros perdidos en la Montaña Solitaria.",
  },
  smaug: {
    name: "Smaug",
    actor: "Smaug",
    race: "Dragón",
    origin: "Erebor",
    weapon: "Fuego",
    image: "https://i.pinimg.com/736x/f6/da/f5/f6daf51ee4d45067c1f907a53adbbd21.jpg",
    description:
      "Smaug es un dragón temido que ocupa la Montaña Solitaria y guarda un vasto tesoro, siendo el principal antagonista de la historia.",
  },
  gollum: {
    name: "Gollum",
    actor: "Gollum",
    race: "Hobbit",
    origin: "Las Montañas Nubladas",
    weapon: "Ninguno",
    image: "https://tolkiengateway.net/w/images/b/bb/John_Howe_-_Gollum.jpg",
    description:
      "Gollum es un ser atormentado por el Anillo Único, que busca recuperar su 'precioso' y juega un papel crucial en la historia de Bilbo.",
  },
  //personajes del libro "gondolin"
  tuor: {
    name: "Tuor",
    actor: "Tuor",
    race: "Hombre",
    origin: "Gondolin",
    weapon: "Espada",
    image: "https://i.pinimg.com/736x/41/b2/0e/41b20ea6e87b5dfa9dc0cb85fbfbc7e1.jpg",
    description:
      "Tuor es un héroe humano que juega un papel crucial en la historia de Gondolin y su caída, conocido por su valentía y determinación.",
  },
  turgon: {
    name: "Turgon",
    actor: "Turgon",
    race: "Elfo",
    origin: "Gondolin",
    weapon: "Espada",
    image: "https://i.redd.it/mc3ygpne82lb1.jpg",
    description:
      "Turgon es el rey de Gondolin y un líder elfo que defiende su ciudad contra las fuerzas de Morgoth.",
  },
  idril: {
    name: "Idril",
    actor: "Idril",
    race: "Elfa",
    origin: "Gondolin",
    weapon: "Ninguno",
    image: "https://i.pinimg.com/736x/08/6d/6c/086d6c5218949dfe159a259c9b739e97.jpg",
    description:
      "Idril es una elfa noble de Gondolin, conocida por su belleza y su papel en la historia de su ciudad y su familia.",
  },
  maeglin: {
    name: "Maeglin",
    actor: "Maeglin",
    race: "Elfo",
    origin: "Gondolin",
    weapon: "Espada",
    image: "https://historiaspulp.com/wp-content/uploads/e84ad5cdc0e8d01db304a0a12d77c1b01fc6d097_00.jpg",
    description:
      "Maeglin es un elfo trágico de Gondolin, conocido por su amor no correspondido y su traición a su ciudad natal.",
  },
  glorfindel: {
    name: "Glorfindel",
    actor: "Glorfindel",
    race: "Elfo",
    origin: "Gondolin",
    weapon: "Espada",
    image: "https://tolkiendili.com/w/images/thumb/0/00/Lotr_glorfindel_by_artalais_d3dfu74.jpg/640px-Lotr_glorfindel_by_artalais_d3dfu74.jpg",
    description:
      "Glorfindel es un elfo valiente de Gondolin, conocido por su sacrificio en la defensa de su ciudad y su regreso en la Segunda Edad.",
  },
  //personajes del libro "El libro de los cuentos perdidos"
  melko: {
    name: "Melko",
    actor: "Melko",
    race: "Vala",
    origin: "Aman",
    weapon: "Ninguno",
    image: "https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEhdY64CfCZkMnk9G7IczCvd7k-l0DIHRxwjZpYlHvyrMISsVEjnSCbwJ8FE2OPUU0W5Q3GPp-ec4A9r9RX4jaVp0bxAdIa3UH8zpp0MGpjJfevSemkSqVGCNfKUc3xgA-RFZzW8Y0wo_6Rt/s1600/melkor2.jpg",
    description:
      "Melko es una de las primeras encarnaciones de Morgoth, conocido por su ambición y deseo de poder en la Tierra Media.",
  },
  tulkas: {
    name: "Tulkas",
    actor: "Tulkas",
    race: "Vala",
    origin: "Aman",
    weapon: "Ninguno",
    image: "https://pm1.aminoapps.com/6713/d0d68a6e72ea2b5be445d90591d0abf3fdbd9637_hq.jpg",
    description:
      "Tulkas es un Vala conocido por su fuerza y valentía, que lucha contra Melko y sus fuerzas en la Tierra Media.",
  },
  eriol: {
    name: "Eriol",
    actor: "Eriol",
    race: "Hombre",
    origin: "La Tierra Media",
    weapon: "Ninguno",
    image: "https://tolkiengateway.net/w/images/thumb/0/01/Vinyatar_-_Limp%C3%AB.png/640px-Vinyatar_-_Limp%C3%AB.png",
    description:
      "Eriol es un viajero humano que se encuentra con los elfos y escucha las historias de la Tierra Media, incluyendo las de Melko y Tulkas.",
  },
  vaire: {
    name: "Vaire",
    actor: "Vaire",
    race: "Vala",
    origin: "Aman",
    weapon: "Ninguno",
    image: "https://i.pinimg.com/736x/74/e8/6b/74e86b01e60da8ca9fa780b84e0c8904.jpg",
    description:
      "Vaire es una Vala conocida por su habilidad para tejer historias y su papel en la creación de la historia de la Tierra Media.",
  },
  teleri: {
    name: "Teleri",
    actor: "Teleri",
    race: "Elfo",
    origin: "Aman",
    weapon: "Ninguno",
    image: "https://64.media.tumblr.com/04caa573a73ab99bbaa0cb1eddbc75d5/35bb1ecfcc0209e5-8a/s2048x3072/93807e9b79fcb3b38ec20ee0aee32b396490295a.jpg",
    description:
      "Teleri es una de las razas élficas que habitan en Aman, conocida por su belleza y conexión con la naturaleza.",
  },
  //personajes del libro "Cuentos inconclusos"

  celebrimor: {
    name: "Celebrimbor",
    actor: "Celebrimbor",
    race: "Elfo",
    origin: "Eregion",
    weapon: "Ninguno",
    image: "https://tolkiendili.com/w/images/8/8d/Jenny_Dolfen_-_Celebrimbor.jpg",
    description:
      "Celebrimbor es un elfo herrero conocido por su habilidad en la forja de anillos de poder, incluyendo los Anillos Élficos.",
  },
  magos_azules: {
    name: "Magos Azules",
    actor: "Magos Azules",
    race: "Maya",
    origin: "Aman",
    weapon: "Ninguno",
    image: "https://sm.ign.com/ign_es/screenshot/default/magos_7ud8.jpg",
    description:
      "Los Magos Azules son dos Maiar que fueron enviados a la Tierra Media para ayudar a los pueblos libres en su lucha contra Sauron, aunque su historia es menos conocida.",
  },
  aladarion: {
    name: "Aladarion",
    actor: "Aladarion",
    race: "Hombre",
    origin: "Númenor",
    weapon: "Espada",
    image: "https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/5f6de1ab-d464-4e8f-9f83-946e413d1c1a/d8jymlf-e548a1d7-a9d2-4b04-870b-1e6dff7aa1d4.jpg?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7InBhdGgiOiJcL2ZcLzVmNmRlMWFiLWQ0NjQtNGU4Zi05ZjgzLTk0NmU0MTNkMWMxYVwvZDhqeW1sZi1lNTQ4YTFkNy1hOWQyLTRiMDQtODcwYi0xZTZkZmY3YWExZDQuanBnIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmZpbGUuZG93bmxvYWQiXX0.l8Yu8jupccvket8cW-7d5aakPsQWSnULY6X94Kt6ODA",
    description:
      "Aladarion es un rey de Númenor conocido por su ambición y su deseo de explorar más allá de las fronteras de su reino, lo que eventualmente llevó a la caída de Númenor.",
  },
  ghân: {
    name: "Ghân-buri-Ghân",
    actor: "Ghân-buri-Ghân",
    race: "Hombre",
    origin: "Dunland",
    weapon: "Ninguno",
    image: "https://lotro-wiki.com/images/thumb/f/f2/Kh%C3%B4r-buri-Gh%C3%A2n.jpg/189px-Kh%C3%B4r-buri-Gh%C3%A2n.jpg",
    description:
      "Ghân-buri-Ghân es un líder de los hombres de Dunland que ayuda a los Rohirrim en su lucha contra Saruman durante la Guerra del Anillo.",
  },
  //personajes del libro "El Señor de los Anillos"
  frodo: {
    name: "Frodo Bolsón",
    actor: "Frodo",
    race: "Hobbit",
    origin: "La Comarca",
    weapon: "Daga",
    image: "https://i.pinimg.com/736x/9f/a7/83/9fa783719f98ada553f92c1f9ecff2ea.jpg",
    description:
      "Frodo Bolsón es el portador del Anillo Único, encargado de llevarlo a Mordor para destruirlo y salvar la Tierra Media.",
  },
  aragon2: {
    name: "Aragorn",
    actor: "Aragorn",
    race: "Hombre",
    origin: "Gondor",
    weapon: "Espada",
    image: "https://i.redd.it/3kkeou0vh8y51.jpg",
    description:
      "Aragorn es el heredero al trono de Gondor y un líder valiente que lucha contra Sauron y ayuda a Frodo en su misión.",
  },gandalf2: {
    name: "Gandalf",
    actor: "Gandalf",
    race: "Maya",
    origin: "Aman",
    weapon: "Bastón",
    image: "https://upload.wikimedia.org/wikipedia/commons/e/ea/GANDALF.jpg",
    description:
      "Gandalf es un mago sabio y poderoso que guía a Frodo y sus compañeros en su lucha contra Sauron y la destrucción del Anillo Único.",
  },
  gollum2: {
    name: "Gollum",
    actor: "Gollum",
    race: "Hobbit",
    origin: "Las Montañas Nubladas",
    weapon: "Ninguno",
    image: "https://tolkiengateway.net/w/images/b/bb/John_Howe_-_Gollum.jpg",
    description:
      "Gollum es un ser atormentado por el Anillo Único, que busca recuperar su 'precioso' y juega un papel crucial en la historia de Frodo.",
  },
  galadriel: {
    name: "Galadriel",
    actor: "Galadriel",
    race: "Elfa",
    origin: "Lothlórien",
    weapon: "Ninguno",
    image: "https://dunesjedi.wordpress.com/wp-content/uploads/2018/09/335edc107a86ee79850583e799469e0d.jpg",
    description:
      "Galadriel es una poderosa elfa y líder de Lothlórien, que ayuda a Frodo y sus compañeros con su sabiduría y regalos mágicos.",
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
