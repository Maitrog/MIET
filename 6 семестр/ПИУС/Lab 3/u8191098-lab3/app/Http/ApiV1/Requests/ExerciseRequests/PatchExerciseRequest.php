<?php

namespace App\Http\ApiV1\Requests\ExerciseRequests;

use Illuminate\Foundation\Http\FormRequest;

class PatchExerciseRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'name' => 'string|max:255|unique:exercises,name',
        ];
    }
}
