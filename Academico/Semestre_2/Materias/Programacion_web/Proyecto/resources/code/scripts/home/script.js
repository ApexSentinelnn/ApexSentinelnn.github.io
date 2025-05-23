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
