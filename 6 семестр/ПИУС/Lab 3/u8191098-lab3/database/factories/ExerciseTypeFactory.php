<?php

namespace Database\Factories;

use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Str;

class ExerciseTypeFactory extends Factory
{
    public function definition()
    {
        return [
            'name'=> Str::random(10),
        ];
    }
}
