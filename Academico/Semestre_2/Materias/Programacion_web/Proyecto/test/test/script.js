// Preloader
window.addEventListener('load', function() {
    const preloader = document.querySelector('.preloader');
    gsap.to(preloader, {
        opacity: 0,
        duration: 0.5,
        ease: "power2.out",
        onComplete: function() {
            preloader.style.display = 'none';
        }
    });
});

// Mobile Navigation
const hamburger = document.querySelector('.hamburger');
const navLinks = document.querySelector('.nav-links');
const navLinkItems = document.querySelectorAll('.nav-link');

hamburger.addEventListener('click', function() {
    this.classList.toggle('active');
    navLinks.classList.toggle('active');
});

navLinkItems.forEach(item => {
    item.addEventListener('click', function() {
        if (window.innerWidth <= 768) {
            hamburger.classList.remove('active');
            navLinks.classList.remove('active');
        }
    });
});

// Smooth Scrolling for Anchor Links
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
        e.preventDefault();
        
        const targetId = this.getAttribute('href');
        const targetElement = document.querySelector(targetId);
        
        if (targetElement) {
            window.scrollTo({
                top: targetElement.offsetTop - 80,
                behavior: 'smooth'
            });
        }
    });
});

// Scroll Reveal Animations
gsap.registerPlugin(ScrollTrigger);

const animateOnScroll = (elements, animationProps) => {
    elements.forEach(element => {
        gsap.from(element, {
            scrollTrigger: {
                trigger: element,
                start: "top 80%",
                toggleActions: "play none none none"
            },
            ...animationProps
        });
    });
};

// Animate Sections
const sections = document.querySelectorAll('.content-section');
animateOnScroll(sections, {
    y: 50,
    opacity: 0,
    duration: 1,
    ease: "power2.out"
});

// Animate Timeline Items
const timelineItems = document.querySelectorAll('.timeline-item');
animateOnScroll(timelineItems, {
    x: -50,
    opacity: 0,
    duration: 0.8,
    stagger: 0.2,
    ease: "power2.out"
});

// Animate Team Members
const teamMembers = document.querySelectorAll('.team-member');
animateOnScroll(teamMembers, {
    y: 50,
    opacity: 0,
    duration: 1,
    stagger: 0.3,
    ease: "power2.out"
});

// Navbar Scroll Effect
window.addEventListener('scroll', function() {
    const nav = document.querySelector('nav');
    if (window.scrollY > 100) {
        nav.classList.add('scrolled');
    } else {
        nav.classList.remove('scrolled');
    }
});

// 3D Background for Hero Section
function initHeroCanvas() {
    const canvas = document.getElementById('hero-canvas');
    if (!canvas) return;

    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    const renderer = new THREE.WebGLRenderer({
        canvas: canvas,
        antialias: true,
        alpha: true
    });
    
    renderer.setSize(window.innerWidth, window.innerHeight);
    
    // Create particles
    const particlesGeometry = new THREE.BufferGeometry();
    const particleCount = 1000;
    
    const posArray = new Float32Array(particleCount * 3);
    for(let i = 0; i < particleCount * 3; i++) {
        posArray[i] = (Math.random() - 0.5) * 10;
    }
    
    particlesGeometry.setAttribute('position', new THREE.BufferAttribute(posArray, 3));
    
    const particlesMaterial = new THREE.PointsMaterial({
        size: 0.02,
        color: 0xd4af37,
        transparent: true,
        opacity: 0.8,
        blending: THREE.AdditiveBlending
    });
    
    const particlesMesh = new THREE.Points(particlesGeometry, particlesMaterial);
    scene.add(particlesMesh);
    
    camera.position.z = 3;
    
    // Animation loop
    function animate() {
        requestAnimationFrame(animate);
        
        particlesMesh.rotation.x += 0.0005;
        particlesMesh.rotation.y += 0.0005;
        
        renderer.render(scene, camera);
    }
    
    animate();
    
    // Handle resize
    window.addEventListener('resize', function() {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth, window.innerHeight);
    });
}

// Initialize everything when DOM is loaded
document.addEventListener('DOMContentLoaded', function() {
    initHeroCanvas();
    
    // Location hover effects
    const locations = document.querySelectorAll('.location');
    locations.forEach(location => {
        location.addEventListener('mouseenter', function() {
            const info = this.querySelector('.location-info');
            gsap.to(info, {
                opacity: 1,
                visibility: 'visible',
                bottom: 'calc(100% + 1rem)',
                duration: 0.3
            });
        });
        
        location.addEventListener('mouseleave', function() {
            const info = this.querySelector('.location-info');
            gsap.to(info, {
                opacity: 0,
                visibility: 'hidden',
                bottom: '100%',
                duration: 0.3
            });
        });
    });
    
    // Team member card flip on mobile
    if (window.innerWidth <= 768) {
        const teamMembers = document.querySelectorAll('.team-member');
        teamMembers.forEach(member => {
            member.addEventListener('click', function() {
                this.querySelector('.member-card').classList.toggle('flipped');
            });
        });
    }
});