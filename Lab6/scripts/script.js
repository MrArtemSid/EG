const sprite_battery = document.getElementById('sprite1');
const sprite_eye = document.getElementById('sprite2');

let sprite_battery_frame = 0;
sprite_battery.addEventListener('click', function() {
    sprite_battery_frame = (sprite_battery_frame + 1) % 4;
    sprite_battery.style.backgroundPosition = `-${sprite_battery_frame * 32}px 0px`;
});

let sprite_eye_frame = 0;
sprite_eye.addEventListener('click', function() {
    sprite_eye_frame = (sprite_eye_frame + 1) % 2;
    sprite_eye.style.backgroundPosition = `-${sprite_eye_frame * 32}px -32px`;
});

function animateSprite() {
    sprite_battery_frame = (sprite_battery_frame + 1) % 4;
    sprite_battery.style.backgroundPosition = `-${sprite_battery_frame * 32}px 0`;
    if (sprite_battery_frame > 1) {
        sprite_eye_frame = 1;
    } else {
        sprite_eye_frame = 0;
    }
    sprite_eye.style.backgroundPosition = `-${sprite_eye_frame * 32}px -32px`;
}

setInterval(animateSprite, 2000);
